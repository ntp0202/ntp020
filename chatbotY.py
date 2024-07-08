import discord
import asyncio
import datetime
import yt_dlp
from discord.ext import commands
import os
from dotenv import load_dotenv
import requests
from googletrans import Translator

load_dotenv()
TOKEN = os.getenv('DiscordToken')
GoogleSearch_API_KEY = os.getenv('Google_API_Key')
SEARCH_ENGINE_ID = os.getenv('Search_Engine_ID')
Weather_API_KEY = os.getenv('Weather_API_Key')

def run_bot():
#Setup
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

    @client.event
    async def on_ready():
        print(f'{client.user} đã kết nối Discord!')

    # Các chức năng của bot
    @client.event
    async def on_message(message):
        # Hiển thị các chức năng hiện có: ?help
        if message.content.startswith("?help"):
            help_message = (
                "Các chức năng hiện có:\n"
                "?vao - Bot vào kênh thoại.\n"
                "?thoat - Bot thoát kênh thoại.\n"
                "?timhinhanh [Tìm kiếm của bạn] - Tìm kiếm hình ảnh trên Google.\n"
                "?dubaothoitiet [Tên thành phố] - Dự báo thời tiết cho thành phố.\n"
                "?phatnhac [Link youtube] - Phát nhạc từ link YouTube.\n"
                "?dungnhac - Dừng phát nhạc.\n"
                "?ngaygio - Hiển thị ngày giờ hiện tại.\n"
                "?dich [Nội dung cần dịch] - Dịch tự động sang tiếng Việt.\n"
            )
            await message.channel.send(help_message)

        # Thiết lập cho bot vào kênh: ?vao
        if message.content.startswith("?vao"):
            try:
                voice_client = await message.author.voice.channel.connect()
                voice_clients[voice_client.guild.id] = voice_client
                await message.channel.send("Bot đã gia nhập kênh thoại.")
            except Exception as e:
                print(e)

        # Thiết lập cho bot thoát kênh: ?thoat
        if message.content.startswith("?thoat"):
            try:
                await voice_clients[message.guild.id].disconnect()
                await message.channel.send("Bot đã thoát kênh thoại.")
            except Exception as e:
                print(e)

        # Thiết lập chức năng tìm kiếm hình ảnh theo google: ?timhinhanh [Tìm kiếm của bạn]
        if message.content.startswith("?timhinhanh"):
            try:
                query = message.content[len("?timhinhanh "):].strip()
                search_url = "https://www.googleapis.com/customsearch/v1"
                params = {
                    "key": GoogleSearch_API_KEY,
                    "cx": SEARCH_ENGINE_ID,
                    "q": query,
                    "searchType": "image",
                    "num": 1 
                }

                response = requests.get(search_url, params=params)
                search_results = response.json()

                if 'items' in search_results:
                    for item in search_results['items']:
                        title = item['title']
                        link = item['link']
                        await message.channel.send(f"**{title}**\n{link}")
                else:
                    await message.channel.send("Không tìm thấy kết quả nào.")
            except Exception as e:
                await message.channel.send(f"Có lỗi xảy ra: {e}")
                print(e)

        # Thiết lập chức năng dự báo thời tiết: ?dubaothoitiet [Tên thành phố]
        if message.content.startswith("?dubaothoitiet"):
            try:
                city = message.content[len("!dubaothoitiet "):].strip()
                weather_url = f"http://api.openweathermap.org/data/2.5/weather?q={city}&appid={Weather_API_KEY}&units=metric&lang=vi"
                
                response = requests.get(weather_url)
                weather_data = response.json()

                if weather_data['cod'] == 200:
                    main = weather_data['weather'][0]['main']
                    description = weather_data['weather'][0]['description']
                    temp = weather_data['main']['temp']
                    humidity = weather_data['main']['humidity']
                    wind_speed = weather_data['wind']['speed']

                    weather_report = (
                        f"Thời tiết tại {city}:\n"
                        f"Trạng thái: {main} - {description}\n"
                        f"Nhiệt độ: {temp}°C\n"
                        f"Độ ẩm: {humidity}%\n"
                        f"Tốc độ gió: {wind_speed} m/s"
                    )
                    await message.channel.send(weather_report)
                else:
                    await message.channel.send("Không thể tìm thấy thông tin thời tiết cho vị trí này.")
            except Exception as e:
                await message.channel.send(f"Có lỗi xảy ra: {e}")
                print(e)

        # Thiết lập chức năng phát nhạc: ?phatnhac [Link youtube]
        if message.content.startswith("?phatnhac"):
            try:
                url = message.content.split()[1]

                loop = asyncio.get_event_loop()
                data = await loop.run_in_executor(None, lambda: ytdl.extract_info(url, download=False))

                song = data['url']
                title = data.get('title', 'Không rõ tên bài hát')
                player = discord.FFmpegOpusAudio(song, **ffmpeg_options)

                voice_clients[message.guild.id].play(player)
                await message.channel.send(f"Đang phát nhạc: {title}")
            except Exception as e:
                print(e)

        # Thiết lập chức năng dừng nhạc: ?dungnhac
        if message.content.startswith("?dungnhac"):
            try:
                voice_clients[message.guild.id].stop()
                await message.channel.send("Đã dừng nhạc.")
            except Exception as e:
                await message.channel.send("Không có bài nhạc nào đang được phát.")
                print(e)

        # Thiết lập chức năng hiển thị ngày giờ: ?ngaygio
        if message.content.startswith("?ngaygio"):
            now = datetime.datetime.now()
            current_time = now.strftime("%H:%M:%S - %d/%m/%Y")
            await message.channel.send(f"Bây giờ là {current_time}")

        # Thiết lập chức năng dịch tự động: ?dich [Nội dung cần dịch]
        if message.content.startswith("?dich"):
            try:
                text_to_translate = message.content[len("?dich "):].strip()
                translator = Translator()
                translated_text = translator.translate(text_to_translate, dest='vi')
                await message.channel.send(translated_text.text)
            except Exception as e:
                await message.channel.send(f"Có lỗi xảy ra khi dịch: {e}")
                print(e)

    client.run(TOKEN)

if __name__ == "__main__":
    run_bot()
