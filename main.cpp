#include <thread>
#include <iostream>
#include <unistd.h> // 包含 getopt 函数的头文件

#include <Prometheus/PrometheusMgr.h>

int main(int argc, char* argv[]) {
    int port = 8080; // 默认端口号

    int opt;
    while ((opt = getopt(argc, argv, "p:")) != -1) {
        switch (opt) {
            case 'p':
                port = std::stoi(optarg); // 将参数值转换为整数
                break;
            default:
                std::cerr << "Usage: " << argv[0] << " -p <port>" << std::endl;
                return 1;
        }
    }
    std::cout << "Port: " << port << std::endl;

    PrometheusMgr::GetInstace().Init("瑶池", "GameServer_1", "localhost", port);

    for (;;) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        const auto random_value_1 = std::rand();
        const auto random_value_2 = std::rand();

        PrometheusMgr::GetInstace().UpdateOnlineUser(random_value_1 % 1000);

        const int32_t msgPrimaryID = random_value_1 % 4;
        const int32_t msgSecondaryID = random_value_2 % 4;
        const int32_t msgSize = random_value_1 % 10000;
        PrometheusMgr::GetInstace().IncrMsgInfo(true, msgPrimaryID, msgSecondaryID, msgSize);
    }

    return 0;
}
