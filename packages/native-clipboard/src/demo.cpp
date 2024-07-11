#include <windows.h>
#include <iostream>
#include <string>
#include <vector>

class ClipboardHistory {
 public:
  void AddItem(HANDLE hBitmap) {
    // Save the bitmap handle to history
    history.push_back(hBitmap);
  }

  void ShowHistory() {
    std::cout << "Clipboard History:" << std::endl;
    for (size_t i = 0; i < history.size(); ++i) {
      std::cout << "Item " << i + 1 << std::endl;
    }
  }

  HANDLE GetItem(size_t index) {
    if (index < history.size()) {
      return history[index];
    }
    return nullptr;
  }

 private:
  std::vector<HANDLE> history;
};

ClipboardHistory clipboardHistory;

void SaveClipboardContent() {
  if (!OpenClipboard(nullptr)) {
    std::cerr << "Failed to open clipboard." << std::endl;
    return;
  }

  HANDLE hData = GetClipboardData(CF_BITMAP);
  if (hData) {
    // Add the bitmap handle to clipboard history
    clipboardHistory.AddItem(hData);
  } else {
    std::cerr << "No bitmap found in clipboard." << std::endl;
  }

  CloseClipboard();
}

int main() {
  std::cout << "Press Enter to save clipboard content, or 'q' to quit." << std::endl;

  while (true) {
    char input;
    std::cin.get(input);

    if (input == 'q') {
      break;
    } else {
      SaveClipboardContent();
      clipboardHistory.ShowHistory();
    }
  }

  return 0;
}
