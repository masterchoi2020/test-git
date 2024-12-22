#include "pch.h"
#include "framework.h"
#include "win32_autoCode.h"

#include <winsock2.h>    // Winsock 라이브러리 헤더
#include <ws2tcpip.h>    // IPv4와 관련된 기능 제공
#include <stdio.h>       // 표준 입출력 헤더

#pragma comment(lib, "ws2_32.lib")  // ws2_32.lib를 링킹하여 Winsock 라이브러리 사용

int main() {
    WSADATA wsadata;
    int result;

    // Winsock 초기화
    result = WSAStartup(MAKEWORD(2, 2), &wsadata);  // Winsock 2.2 버전 요청
    if (result != 0) {
        printf("Winsock 초기화 실패: %d\n", result);
        return 1;  // 실패 시 프로그램 종료
    }

    // 호스트 이름을 가져오기
    char localhostname[MAX_PATH];
    result = gethostname(localhostname, sizeof(localhostname));  // 로컬 호스트 이름 가져오기
    if (result != 0) {
        printf("호스트 이름을 가져오는 데 실패했습니다.\n");
        WSACleanup();  // 초기화된 Winsock 종료
        return 1;
    }

    // 호스트 이름에 대한 IP 주소 가져오기
    struct hostent* host = gethostbyname(localhostname);  // 호스트 이름에 대한 IP 주소 정보 얻기
    if (host == NULL) {
        printf("호스트 이름을 IP 주소로 변환할 수 없습니다.\n");
        WSACleanup();  // 초기화된 Winsock 종료
        return 1;
    }

    // IP 주소 출력
    struct in_addr* addr = (struct in_addr*)host->h_addr_list[0];  // 첫 번째 IP 주소 가져오기
    printf("내 IP 주소: %s\n", inet_ntoa(*addr));  // IP 주소를 문자열로 변환하여 출력

    // Winsock 종료
    WSACleanup();

    return 0;
}
