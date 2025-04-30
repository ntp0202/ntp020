#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <ctime>
using namespace std;

struct Process {
    char name;
    int arrival_time;
    int burst_time;
    int start_time;
    int finish_time;
    int waiting_time;
    int turnaround_time;
    int response_time;
    bool completed = false;
};

struct GanttEntry {
    int time;
    char process_name;
};

bool compareArrival(Process a, Process b) {
    return a.arrival_time < b.arrival_time;
}

void Input(Process* p, int n) {
    srand(time(0));
    for (int i = 0; i < n; i++) {
        p[i].name = 'A' + i;
        p[i].arrival_time = rand() % 21;          // [0, 20]
        p[i].burst_time = 2 + rand() % 11;         // [2, 12]
        cout << "Process " << p[i].name 
             << " | Arrival: " << p[i].arrival_time 
             << " | Burst: " << p[i].burst_time << endl;
    }
}

void SJF_NonPreemptive(Process* p, int n, vector<GanttEntry>& gantt) {
    int current_time = 0;
    int completed = 0;
    double total_wt = 0, total_tt = 0, total_rt = 0;

    while (completed < n) {
        int idx = -1;
        int min_bt = 1e9;

        for (int i = 0; i < n; i++) {
            if (!p[i].completed && p[i].arrival_time <= current_time) {
                if (p[i].burst_time < min_bt) {
                    min_bt = p[i].burst_time;
                    idx = i;
                }
            }
        }

        if (idx == -1) {
            current_time++; // không có tiến trình nào đến, tăng thời gian
            continue;
        }

        p[idx].start_time = current_time;
        p[idx].finish_time = current_time + p[idx].burst_time;
        p[idx].turnaround_time = p[idx].finish_time - p[idx].arrival_time;
        p[idx].waiting_time = p[idx].start_time - p[idx].arrival_time;
        p[idx].response_time = p[idx].waiting_time;
        p[idx].completed = true;

        current_time = p[idx].finish_time;
        completed++;

        total_tt += p[idx].turnaround_time;
        total_wt += p[idx].waiting_time;
        total_rt += p[idx].response_time;

        gantt.push_back({p[idx].start_time, p[idx].name});
    }

    // Kết quả chi tiết từng tiến trình
    cout << "\nProcess   Arrival  Burst  Start  Finish  Wait  Turnaround  Response\n";
    for (int i = 0; i < n; i++) {
        cout << "   " << p[i].name
             << setw(10) << p[i].arrival_time
             << setw(7) << p[i].burst_time
             << setw(7) << p[i].start_time
             << setw(8) << p[i].finish_time
             << setw(6) << p[i].waiting_time
             << setw(11) << p[i].turnaround_time
             << setw(10) << p[i].response_time << endl;
    }

    cout << fixed << setprecision(2);
    cout << "\nAverage Waiting Time: " << total_wt / n << endl;
    cout << "Average Turnaround Time: " << total_tt / n << endl;
    cout << "Average Response Time: " << total_rt / n << endl;
}

void printGanttChart(const vector<GanttEntry>& gantt, int last_time) {
    cout << "\n--- Gantt Chart ---\n";
    cout << "|";
    for (auto& g : gantt) {
        cout << "  " << g.process_name << "  |";
    }
    cout << "\n";

    for (size_t i = 0; i < gantt.size(); ++i) {
        cout << gantt[i].time;
        if (i < gantt.size() - 1) cout << setw(7);
    }
    cout << setw(7) << last_time << endl;
}

int main() {
    int n;
    cout << "Nhap so luong tien trinh (>=5): ";
    cin >> n;
    if (n < 5) {
        cout << "Vui long nhap it nhat 5 tien trinh tro len.\n";
        return 1;
    }

    Process* p = new Process[n];
    vector<GanttEntry> gantt;

    Input(p, n);
    sort(p, p + n, compareArrival); // sắp xếp theo thời gian đến

    SJF_NonPreemptive(p, n, gantt);

    printGanttChart(gantt, gantt.back().time + p[gantt.back().process_name - 'A'].burst_time);

    delete[] p;
    return 0;
}
