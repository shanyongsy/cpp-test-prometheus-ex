#pragma once
#include <memory>

namespace prometheus
{
    class Exposer;
    class Registry;
    class Counter;
    class Gauge;    

    template <typename T>
    class Family;
};

class PrometheusMgr
{
public:
   	PrometheusMgr();
	~PrometheusMgr();

    static PrometheusMgr& GetInstace()
	{
		static PrometheusMgr s_inc;
		return s_inc;
	}

    // 初始化
    // zoneName: 区服名称（瑶池、九龙岛、76、等）
    // serverName: 实例名称（GameServer_1、Goddess、等）
    // listenPort: 监听端口
    void Init(const char* zoneName, const char* serverName,const char* listenIP, int32_t listenPort);

    // 更新在线人数
    void UpdateOnlineUser(int32_t count);

    // 增加消息计数
    // isSend: 是否是发送消息
    // msgPrimaryID: 消息主ID
    // msgSecondaryID: 消息次ID
    // msgSize: 消息大小
    void IncrMsgInfo(bool isSend, int32_t msgPrimaryID, int32_t msgSecondaryID, int32_t msgSize);
private:
    // 区服名称(yaochi、jiulongdao、76、等)
    std::string m_zoneName;
    // 实例名称(GameServer_1、Goddess、等)
    std::string m_serverName;
    // 监听IP
    std::string m_listenIP;
    // 监听端口
    int32_t m_listenPort;

private:
    prometheus::Exposer* exposer;
    std::shared_ptr<prometheus::Registry> registry;
    prometheus::Family<prometheus::Gauge>* user_gauge_family;
    prometheus::Family<prometheus::Counter>* msg_counter_family;
    prometheus::Family<prometheus::Counter>* msg_size_family;
};
