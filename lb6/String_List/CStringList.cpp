#include "CStringList.h"

CStringList::~CStringList() 
{
    Clear();
}

CStringList::CStringList(const CStringList& other)
{
    try
    {
        for (const auto& str : other)
        {
            PushBack(str);
        }
    }
    catch (...)
    {
        Clear();
        throw;
    }
}

CStringList::CStringList(CStringList&& other) noexcept
{
    Swap(other);
}

CStringList::CStringList(std::initializer_list<std::string> init)
{
    CStringList tmp;
    for (const auto& str : init)
    {
        tmp.PushBack(str);
    }
    Swap(tmp);
}

CStringList& CStringList::operator=(const CStringList& other)
{
    if (this != &other)
    {
        CStringList tmp(other);
        Swap(tmp);
    }
    return *this;
}

CStringList& CStringList::operator=(CStringList&& other) noexcept
{
    if (this != &other)
    {
        Clear();
        Swap(other);
    }
    return *this;
}

void CStringList::PushBack(const std::string& str) 
{
    auto new_node = std::make_unique<Node>(str);
    PushBack(std::move(new_node));
}

void CStringList::PushBack(std::string&& str) 
{
    auto new_node = std::make_unique<Node>(std::move(str));
    PushBack(std::move(new_node));
}

void CStringList::PushFront(const std::string& str) 
{
    auto new_node = std::make_unique<Node>(str);
    PushFront(std::move(new_node));
}

void CStringList::PushFront(std::string&& str)
{
    auto new_node = std::make_unique<Node>(std::move(str));
    PushFront(std::move(new_node));
}

void CStringList::Clear() noexcept
{
    while (m_head)
    {
        m_head = std::move(m_head->next);
    }
    m_tail = nullptr;
    m_size = 0;
}

void CStringList::Swap(CStringList& other) noexcept
{
    std::swap(m_head, other.m_head);
    std::swap(m_tail, other.m_tail);
    std::swap(m_size, other.m_size);
}

void CStringList::PushBack(std::unique_ptr<Node>&& new_node) noexcept
{
    Node* new_tail = new_node.get();
    if (m_tail)
    {
        m_tail->next = std::move(new_node);
        new_tail->prev = m_tail;
        m_tail = new_tail;
    }
    else
    {
        m_head = std::move(new_node);
        m_tail = m_head.get();
    }
    ++m_size;
}

void CStringList::PushFront(std::unique_ptr<Node>&& new_node) noexcept
{
    new_node->next = std::move(m_head);
    if (new_node->next)
    {
        new_node->next->prev = new_node.get();
    }
    else
    {
        m_tail = new_node.get();
    }
    m_head = std::move(new_node);
    ++m_size;
}