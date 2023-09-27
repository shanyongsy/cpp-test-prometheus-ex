#include <prometheus/exposer.h>
#include <prometheus/registry.h>
#include <prometheus/gauge.h>
#include <prometheus/family.h>
#include <prometheus/counter.h>

#include "PrometheusMgr.h"

using namespace prometheus;

PrometheusMgr::PrometheusMgr()
    : m_exposer(nullptr), m_registry(nullptr), user_gauge_family(nullptr)
{
    // 在构造函数中执行任何必要的初始化
}

PrometheusMgr::~PrometheusMgr()
{
    UnInit();
}

void PrometheusMgr::Init(const char* serverName, const char*  instanceName, int32_t listenPort)
{
    // 保存参数
    m_serverName = serverName;
    m_instanceName = instanceName;
    m_listenPort = listenPort;

    // 创建Prometheus注册表
    m_registry = std::make_shared<Registry>();

    // 创建Prometheus暴露器
    m_exposer = new Exposer("localhost:" + std::to_string(listenPort));

    // 创建在线用户的Gauge指标
   user_gauge_family = std::shared_ptr<Family<Gauge>>(
   &BuildGauge().Name("online_users").Help("Number of online users").Register(*m_registry));
    
    // 创建消息计数器的Family
    msg_counter_family = std::shared_ptr<Family<Counter>>(
    &BuildCounter().Name("message_count").Help("Count of messages").Register(*m_registry));

    // 创建消息大小的Family
    msg_size_family = std::shared_ptr<Family<Counter>>(
    &BuildCounter().Name("message_size").Help("Size of messages").Register(*m_registry));

    // 启动Prometheus暴露器
    m_exposer->RegisterCollectable(m_registry);
}

void PrometheusMgr::UnInit()
{
    // 停止Prometheus暴露器
    if (m_exposer)
    {
        delete m_exposer;
        m_exposer = nullptr;
    }
}

void PrometheusMgr::UpdateOnlineUser(int32_t count)
{
    if(nullptr == user_gauge_family)
    {
        return;
    }

    // 设置在线用户的Gauge指标的值
    auto& gauge = user_gauge_family->Add({
        {"server_name", m_serverName},
        {"instance_name", m_instanceName}
        });
    gauge.Set(count);
    
}

void PrometheusMgr::IncrMsgInfo(bool isSend, int32_t msgPrimaryID, int32_t msgSecondaryID, int32_t msgSize)
{
    // 使用Family创建消息计数器，并增加计数
    auto& msg_counter = msg_counter_family->Add({
        {"server_name", m_serverName},
        {"instance_name", m_instanceName},
        {"direction", isSend ? "send" : "receive"},
        {"primary_id", std::to_string(msgPrimaryID)},
        {"secondary_id", std::to_string(msgSecondaryID)},
        });
    msg_counter.Increment();

    // 使用Family创建消息大小的Gauge指标，并设置值
    auto& msg_size = msg_size_family->Add({
        {"server_name", m_serverName},
        {"instance_name", m_instanceName},
        {"direction", isSend ? "send" : "receive"},
        {"primary_id", std::to_string(msgPrimaryID)},
        {"secondary_id", std::to_string(msgSecondaryID)},
        });
    msg_size.Increment(msgSize);
}
