#include "effect_manager.h"
#include"effect/catch_effect/catch_effect.h"
#include"effect/drop_effect/drop_effect.h"
#include"effect/hit_effect/hit_effect.h"

CEffectManager& CEffectManager::GetInstance(void)
{
    static CEffectManager instance;
    return instance;
}

void CEffectManager::Initialize(void)
{
    m_EffectList.clear();
}

void CEffectManager::Update(void)
{
    //リストが空なら終了
    if (m_EffectList.empty())return;

    EFFECT_LIST::iterator it = m_EffectList.begin();

    while (it != m_EffectList.end())
    {
        IEffect* effect = (IEffect*)(*it);
        effect->Update();

        //エフェクトが非アクティブなら削除してリストから外す
        if (!effect->GetActive())
        {
            effect->Finalize();
            delete effect;
            it = m_EffectList.erase(it);
            continue;
        }
        ++it;
    }
}

void CEffectManager::Draw(void)
{
    if (m_EffectList.empty())return;

    EFFECT_LIST::iterator it = m_EffectList.begin();

    while (it != m_EffectList.end())
    {
        (*it)->Draw();
        ++it;
    }
}

void CEffectManager::Finalize(void)
{
    if (m_EffectList.empty())return;

    EFFECT_LIST::iterator it = m_EffectList.begin();

    while (it != m_EffectList.end())
    {
        (*it)->Finalize();
        delete(*it);
        ++it;
    }
    m_EffectList.clear();
}

void CEffectManager::Create(EFFECT_ID id, const vivid::Vector2& pos, unsigned int color, float rotation)
{
    IEffect* effect = nullptr;
    switch (id)
    {
    case EFFECT_ID::CATCH:effect = new CCatchEffect(); break;
    case EFFECT_ID::DROP: effect = new CDropEffect(); break;
    case EFFECT_ID::HIT: effect = new CHitEffect(); break;
    }
    if (!effect)return;

    effect->Initialize(pos, color, rotation);
    m_EffectList.push_back(effect);
}

CEffectManager::CEffectManager(void)
{
}

CEffectManager::CEffectManager(const CEffectManager& rhs)
{
    (void)rhs;
}

CEffectManager::~CEffectManager(void)
{
}

CEffectManager& CEffectManager::operator=(const CEffectManager& rhs)
{
    (void)rhs;
    return *this;
}
