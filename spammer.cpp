#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <windows.h>

void sendKeystrokes(const std::string& message, int delay) {
    for (char ch : message) {
        SHORT vk = VkKeyScan(ch);
        if ((vk & 0xFF00) != 0) {
            keybd_event(VK_SHIFT, 0, 0, 0);
        }
        keybd_event(vk & 0xFF, 0, 0, 0);
        keybd_event(vk & 0xFF, 0, KEYEVENTF_KEYUP, 0);
        if ((vk & 0xFF00) != 0) {
            keybd_event(VK_SHIFT, 0, KEYEVENTF_KEYUP, 0);
        }
    }
    keybd_event(VK_RETURN, 0, 0, 0);
    keybd_event(VK_RETURN, 0, KEYEVENTF_KEYUP, 0);
    std::this_thread::sleep_for(std::chrono::milliseconds(delay));
}

void spamViaPaste(int repetitions, int delay) {
    for (int i = 0; i < repetitions; ++i) {
        keybd_event(VK_CONTROL, 0, 0, 0);
        keybd_event('V', 0, 0, 0);
        keybd_event('V', 0, KEYEVENTF_KEYUP, 0);
        keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
        keybd_event(VK_RETURN, 0, 0, 0);
        keybd_event(VK_RETURN, 0, KEYEVENTF_KEYUP, 0);
        std::this_thread::sleep_for(std::chrono::milliseconds(delay));
    }
}

void spamSlashCommand(int repetitions, int delay) {
    for (int i = 0; i < repetitions; ++i) {
        keybd_event(VkKeyScan('/'), 0, 0, 0);
        keybd_event(VkKeyScan('/'), 0, KEYEVENTF_KEYUP, 0);
        keybd_event(VK_RETURN, 0, 0, 0);
        keybd_event(VK_RETURN, 0, KEYEVENTF_KEYUP, 0);
        std::this_thread::sleep_for(std::chrono::milliseconds(delay));
    }
}

int main() {
    while (true) {
        int choice;
        std::cout << "Choose spam method: 1 (custom message) | 2 (paste) | 3 (slash command): ";
        std::cin >> choice;

        if (choice == 1 || choice == 2 || choice == 3) {
            int repetitions;
            std::cout << "Enter number of repetitions (0 to exit, 1 to change choice): ";
            std::cin >> repetitions;
            if (repetitions == 0) exit(0);
            if (repetitions == 1) continue;

            int delay;
            std::cout << "Enter delay between messages (ms): ";
            std::cin >> delay;

            if (choice == 1) {
                std::string message;
                std::cout << "Enter the message to spam: ";
                std::cin.ignore();
                std::getline(std::cin, message);
                std::cout << "Spamming in 5 seconds...\n";
                std::this_thread::sleep_for(std::chrono::seconds(5));
                for (int i = 0; i < repetitions; ++i) {
                    sendKeystrokes(message, delay);
                }
            }
            else if (choice == 2) {
                std::cout << "Spamming with paste in 5 seconds...\n";
                std::this_thread::sleep_for(std::chrono::seconds(5));
                spamViaPaste(repetitions, delay);
            }
            else if (choice == 3) {
                std::cout << "Spamming with '/' command in 5 seconds...\n";
                std::this_thread::sleep_for(std::chrono::seconds(5));
                spamSlashCommand(repetitions, delay);
            }
        }
    }
    return 0;
}
