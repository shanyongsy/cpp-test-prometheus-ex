#include <prometheus/exposer.h>
#include <prometheus/registry.h>
#include <prometheus/gauge.h>
#include <prometheus/family.h>
#include <prometheus/counter.h>

#include <Prometheus/PrometheusMgr.h>

using namespace prometheus;

PrometheusMgr::PrometheusMgr(): 
    exposer(nullptr), 
    registry(nullptr), 
    user_gauge_family(nullptr), 
    msg_counter_family(nullptr), 
    msg_size_family(nullptr)
{
    // 在构造函数中执行任何必要的初始化
}

PrometheusMgr::~PrometheusMgr()
{
	if (exposer)
	{
		delete exposer;
		exposer = nullptr;
	}
}

void PrometheusMgr::Init(const char* zoneName, const char* serverName,const char* listenIP, int32_t listenPort)
{
    // 保存参数
    m_zoneName = zoneName;
    m_serverName = serverName;
    m_listenIP = listenIP;
    m_listenPort = listenPort;

    // 创建Prometheus暴露器
    exposer = new Exposer(m_listenIP + ":" + std::to_string(listenPort));

    // 创建Prometheus注册表
    registry = std::make_shared<Registry>();

    // 创建在线用户的Gauge指标
   user_gauge_family = &BuildGauge().Name("online_users").Help("Number of online users").Register(*registry);
    
    // 创建消息计数器的Family
    msg_counter_family = &BuildCounter().Name("message_count").Help("Count of messages").Register(*registry);

    // 创建消息大小的Family
    msg_size_family = &BuildCounter().Name("message_size").Help("Size of messages").Register(*registry);

    // 启动Prometheus暴露器
    exposer->RegisterCollectable(std::weak_ptr<Collectable>(registry));
}

void PrometheusMgr::UpdateOnlineUser(int32_t count)
{
    if(nullptr == user_gauge_family)
        return;

    // 设置在线用户的Gauge指标的值
    auto& gauge = user_gauge_family->Add({
        {"zone_name", m_zoneName},
        {"server_name", m_serverName}
        });
    gauge.Set(count);    
}

void PrometheusMgr::IncrMsgInfo(bool isSend, int32_t msgPrimaryID, int32_t msgSecondaryID, int32_t msgSize)
{
    if(nullptr != msg_counter_family)
    {
        // 使用Family创建消息计数器，并增加计数
        auto& msg_counter = msg_counter_family->Add({
            {"zone_name", m_zoneName},
            {"server_name", m_serverName},
            {"direction", isSend ? "send" : "receive"},
            {"primary_id", std::to_string(msgPrimaryID)},
            {"secondary_id", std::to_string(msgSecondaryID)},
            });
        msg_counter.Increment();
    }

    if(nullptr != msg_size_family)
    {
        // 使用Family创建消息大小的Gauge指标，并设置值
        auto& msg_size = msg_size_family->Add({
            {"zone_name", m_zoneName},
            {"server_name", m_serverName},
            {"direction", isSend ? "send" : "receive"},
            {"primary_id", std::to_string(msgPrimaryID)},
            {"secondary_id", std::to_string(msgSecondaryID)},
            });
        msg_size.Increment(msgSize);
    }
}
