#include <pcap.h>
#include <iostream>
#include <string>
#include <conio.h> // For _kbhit() and _getch()

int main() {
    char errorBuffer[PCAP_ERRBUF_SIZE];
    pcap_if_t *allDevices, *device;
    int deviceNumber = 0;
    pcap_t *handle;
    pcap_dumper_t *pcapFile; // To save packets to a file

    // Retrieve the list of available devices
    if (pcap_findalldevs(&allDevices, errorBuffer) == -1) {
        std::cerr << "Error finding devices: " << errorBuffer << std::endl;
        return 1;
    }

    // List all devices
    std::cout << "Available devices:" << std::endl;
    int i = 0;
    for (device = allDevices; device; device = device->next) {
        std::cout << ++i << ". " << (device->name ? device->name : "Unknown device") << std::endl;
        if (device->description) {
            std::cout << "   (" << device->description << ")" << std::endl;
        }
    }

    // Ask the user to select a device
    std::cout << "Enter the number of the device to use: ";
    std::cin >> deviceNumber;

    // Find the chosen device
    device = allDevices;
    for (i = 1; i < deviceNumber && device; ++i) {
        device = device->next;
    }

    if (!device) {
        std::cerr << "Invalid device number." << std::endl;
        pcap_freealldevs(allDevices);
        return 1;
    }

    // Open the device for capturing
    handle = pcap_open_live(device->name, 65536, 1, 1000, errorBuffer);
    if (!handle) {
        std::cerr << "Error opening device: " << errorBuffer << std::endl;
        pcap_freealldevs(allDevices);
        return 1;
    }

    // Open a file to save the captured packets
    pcapFile = pcap_dump_open(handle, "captured_packets.pcap");
    if (!pcapFile) {
        std::cerr << "Error opening file to save packets: " << pcap_geterr(handle) << std::endl;
        pcap_close(handle);
        pcap_freealldevs(allDevices);
        return 1;
    }

    std::cout << "Capturing packets. Press 'o' to stop..." << std::endl;

    // Capture packets in a loop
    struct pcap_pkthdr *header;
    const u_char *data;
    int result;
    while (true) {
        result = pcap_next_ex(handle, &header, &data);
        if (result == 1) { // A packet was captured
            pcap_dump((u_char *)pcapFile, header, data);
        } else if (result == 0) {
            // Timeout expired
            continue;
        } else {
            // An error occurred
            std::cerr << "Error capturing packet: " << pcap_geterr(handle) << std::endl;
            break;
        }

        // Check for user input to stop
        if (_kbhit() && _getch() == 'o') {
            std::cout << "Stopping capture..." << std::endl;
            break;
        }
    }

    // Close the file and free resources
    pcap_dump_close(pcapFile);
    pcap_close(handle);
    pcap_freealldevs(allDevices);

    std::cout << "Packets saved to 'captured_packets.pcap' in the current folder." << std::endl;

    return 0;
}
