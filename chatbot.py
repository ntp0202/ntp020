import discord
import os
import asyncio
import yt_dlp
import datetime
import requests
from dotenv import load_dotenv
from googleapiclient.discovery import build

load_dotenv()
TOKEN = os.getenv('Discord_TOKEN')
Weather_API_KEY = os.getenv('OpenWeatherMap_API_Key')
GoogleSearch_API_KEY = os.getenv('Google_API_Key')
SEARCH_ENGINE_ID = os.getenv('Search_Engine_ID')

def run_bot():
    # Setup
    intents = discord.Intents.default()
    intents.message_content = True
    client = discord.Client(intents=intents)

    voice_clients = {}
    yt_dl_options = {"format": "bestaudio/best"}
    ytdl = yt_dlp.YoutubeDL(yt_dl_options)

    ffmpeg_options = {
        'before_options': '-reconnect 1 -reconnect_streamed 1 -reconnect_delay_max 5',
        'options': '-vn -filter:a "volume=0.25"'
    }

    # Danh sách các lệnh
    command_descriptions = {
        "!vaokenh": "Thiết lập cho bot vào kênh thoại.",
        "!choinhac [Link youtube]": "Thiết lập chạy nhạc từ một đường link YouTube.",
        "!tatnhac": "Thiết lập tắt nhạc đang phát.",
        "!thoatkenh": "Thiết lập cho bot thoát kênh thoại.",
        "!ngaygio": "Hiển thị thời gian hiện tại.",
        "!datbaothuc [Giờ:Phút]": "Đặt báo thức vào một thời điểm cụ thể.",
        "!dubaothoitiet [tên thành phố]": "Dự báo thời tiết cho một thành phố cụ thể.",
        "!timkiem [từ khóa]": "Tìm kiếm và hiển thị kết quả hình ảnh từ Google."
    }

    @client.event
    async def on_ready():
        print(f'{client.user} đã kết nối Discord!')

    # Các chức năng
    @client.event
    async def on_message(message):
        # Cài đặt chạy nhạc cho bot
        if message.content.startswith("!vaokenh"):  # Thiết lập cho bot vào kênh thoại: !vaokenh
            try:
                voice_client = await message.author.voice.channel.connect()
                voice_clients[voice_client.guild.id] = voice_client
                await message.channel.send("Bot đã vào kênh thoại.")
            except Exception as e:
                print(e)

        if message.content.startswith("!choinhac"): # Thiết lập chạy nhạc cho bot: !choinhac [Link youtube]
            try:
                url = message.content.split()[1]

                loop = asyncio.get_event_loop()
                data = await loop.run_in_executor(None, lambda: ytdl.extract_info(url, download=False))

                song = data['url']
                title = data.get('title', 'Không rõ tên bài hát')
                player = discord.FFmpegOpusAudio(song, **ffmpeg_options)

                voice_clients[message.guild.id].play(player)
                await message.channel.send(f"Đang chạy nhạc: {title}")
            except Exception as e:
                print(e)

        if message.content.startswith("!tatnhac"): # Thiết lập tắt nhạc cho bot: !tatnhac
            try:
                voice_clients[message.guild.id].stop()
                await message.channel.send("Đã dừng nhạc.")
            except Exception as e:
                print(e)

        if message.content.startswith("!thoatkenh"): # Thiết lập cho bot thoát kênh thoại: !thoatkenh
            try:
                await voice_clients[message.guild.id].disconnect()
                await message.channel.send("Bot đã thoát kênh thoại.")
            except Exception as e:
                print(e)

        # Cài đặt hiển thị ngày giờ cho bot
        if message.content.startswith("!ngaygio"):
            current_time = datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S")
            await message.channel.send(f'Hiện tại là: {current_time}')

        # Đặt báo thức
        if message.content.startswith("!datbaothuc"):
            try:
                time_str = message.content.split()[1]
                alarm_time = datetime.datetime.strptime(time_str, "%H:%M").time()
                await message.channel.send(f'Đã cài đặt báo thức lúc {time_str}.')
                
                while True:
                    now = datetime.datetime.now().time()
                    if now >= alarm_time:
                        try:
                            url = "https://www.youtube.com/watch?v=57bOglax2yE"
                            loop = asyncio.get_event_loop()
                            data = await loop.run_in_executor(None, lambda: ytdl.extract_info(url, download=False))

                            song = data['url']
                            player = discord.FFmpegOpusAudio(song, **ffmpeg_options)

                            voice_clients[message.guild.id].play(player)
                            await message.channel.send("Báo thức! Đang phát nhạc chuông.")
                        except Exception as e:
                            print(e)
                        break
                    await asyncio.sleep(5)
            except Exception as e:
                await message.channel.send("Vui lòng cung cấp thời gian báo thức hợp lệ (định dạng HH:MM).")
                print(e)

        # Dự báo thời tiết
        if message.content.startswith("!dubaothoitiet"):  
            try:
                city = message.content.split(' ', 1)[1]
                base_url = "http://api.openweathermap.org/data/2.5/weather"
                params = {
                    "q": city,
                    "appid": Weather_API_KEY,
                    "units": "metric"  # Để lấy dự báo theo đơn vị Celsius
                }

                response = requests.get(base_url, params=params)
                data = response.json()

                if data["cod"] == "404":
                    await message.channel.send(f"Không tìm thấy thông tin thời tiết cho thành phố {city}.")
                else:
                    weather_desc = data["weather"][0]["description"]
                    temp = data["main"]["temp"]
                    humidity = data["main"]["humidity"]

                    vietnamese_weather_desc = {
                        "clear sky": "Trời quang đãng",
                        "few clouds": "Ít mây",
                        "scattered clouds": "Mây rải rác",
                        "broken clouds": "Mây rải rác",
                        "overcast clouds": "Trời âm u",
                        "mist": "Sương mù",
                        "light rain": "Mưa nhẹ",
                        "moderate rain": "Mưa vừa",
                        "heavy intensity rain": "Mưa lớn",
                        "very heavy rain": "Mưa rất lớn",
                        "extreme rain": "Mưa cực lớn",
                        "freezing rain": "Mưa đá",
                        "light snow": "Tuyết nhẹ",
                        "snow": "Tuyết",
                        "heavy snow": "Tuyết nặng hạt",
                        "sleet": "Mưa tuyết",
                        "shower rain": "Mưa rào",
                        "thunderstorm": "Dông",
                        "thunderstorm with light rain": "Dông và mưa nhẹ",
                        "thunderstorm with rain": "Dông và mưa",
                        "thunderstorm with heavy rain": "Dông và mưa lớn",
                        "thunderstorm with light drizzle": "Dông và mưa phùn",
                        "thunderstorm with drizzle": "Dông và mưa phùn",
                        "thunderstorm with heavy drizzle": "Dông và mưa phùn lớn"
                    }

                    if weather_desc in vietnamese_weather_desc:
                        weather_desc_vi = vietnamese_weather_desc[weather_desc]
                    else:
                        weather_desc_vi = weather_desc.capitalize()

                    await message.channel.send(f"Thời tiết tại {city}: "
                                               f"{weather_desc_vi}, "
                                               f"Nhiệt độ: {temp}°C, "
                                               f"Độ ẩm: {humidity}%.")

            except Exception as e:
                await message.channel.send("Vui lòng cung cấp tên thành phố sau lệnh !dubaothoitiet.")
                print(e)

        # Google search
        if message.content.startswith("!timkiem"):
            try:
                query = message.content.split(' ', 1)[1]
                service = build("customsearch", "v1", developerKey=GoogleSearch_API_KEY)
                result = service.cse().list(q=query, cx=SEARCH_ENGINE_ID, num=5, lr="lang_vi", cr="countryVN", searchType="image").execute()
                search_results = result.get('items', [])

                if search_results:
                    response = "\n".join([f"{item['title']}: {item['link']}" for item in search_results])
                    await message.channel.send(f"Kết quả tìm kiếm hình ảnh cho '{query}':\n{response}")
                else:
                    await message.channel.send(f"Không tìm thấy kết quả hình ảnh nào cho '{query}'.")

            except Exception as e:
                await message.channel.send("Đã xảy ra lỗi trong quá trình tìm kiếm.")
                print(e)

        # Hiển thị danh sách các lệnh sẵn có
        if message.content.startswith("!help"):
            help_message = "Danh sách các lệnh và mô tả:\n\n"
            for command, description in command_descriptions.items():
                help_message += f"{command}: {description}\n"
            await message.channel.send(help_message)

    client.run(TOKEN)

if __name__ == "__main__":
    run_bot()
