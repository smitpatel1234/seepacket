# Packet Capture Tool (Windows)

This project is a **Windows-based packet capture tool** built using C++ and the **WinPcap/Npcap** library.  
It captures network packets and stores them in a `capture.pcap` file for later analysis.

## 🚀 Features

- Captures live network packets
- Saves captured packets in **PCAP format**
- Uses **Npcap/WinPcap** for packet sniffing
- Works on **Windows**

---

## 🛠 Prerequisites

### 1️⃣ Install Npcap
Before running this tool, install **Npcap** from:  
🔗 [Npcap Official Site](https://nmap.org/npcap/)  

Make sure to install it with **"WinPcap API Compatibility Mode"** enabled.

---

## 📥 Setup & Compilation

### 2️⃣ Compilation
The project includes a precompiled executable **(`packet_capture.exe`)**, but if you want to compile it yourself, use the following command:

```bash
g++ -o packet_capture smit.cpp ^
   -I"C:/path/packet_cpature_tool/WpdPack_4_1_2/WpdPack/Include" ^
   -L"C:/path/packet_cpature_tool/WpdPack_4_1_2/WpdPack/Lib/x64" ^
   -lwpcap -liphlpapi -lws2_32
