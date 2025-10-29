#include <memory>
#include <string>
#include <iterator>
#include <stdexcept>
#include <initializer_list>

class CStringList 
{
private:
    struct Node 
    {
        std::string data;
        std::unique_ptr<Node> next;
        Node* prev = nullptr;

        explicit Node(std::string str) : data(std::move(str)) {}
    };

    std::unique_ptr<Node> m_head;
    Node* m_tail = nullptr;
    size_t m_size = 0;

    void PushBack(std::unique_ptr<Node>&& new_node) noexcept;

    void PushFront(std::unique_ptr<Node>&& new_node) noexcept;

public:

    template <bool IsConst>

    class Iterator 
    {
    private:
        using node_type = std::conditional_t<IsConst, const Node, Node>;
        node_type* m_node = nullptr;
        const CStringList* m_parent = nullptr;
        template<bool> friend class Iterator;

    public:
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = std::conditional_t<IsConst, const std::string, std::string>;
        using difference_type = std::ptrdiff_t;
        using pointer = value_type*;
        using reference = value_type&;

        explicit Iterator(node_type* node, const CStringList* parent = nullptr)
            : m_node(node), m_parent(parent) {}

        reference operator*() const 
        {
            if (!m_node) 
                throw std::out_of_range("Dereferencing end iterator");
            return m_node->data;
        }

        pointer operator->() const 
        {
            if (!m_node) 
                throw std::out_of_range("Accessing end iterator");
            return &m_node->data;
        }

        Iterator& operator++() 
        {
            if (!m_node) 
                throw std::out_of_range("Incrementing end iterator");
            m_node = m_node->next.get();
            return *this;
        }

        Iterator operator++(int) 
        {
            Iterator tmp = *this;
            ++*this;
            return tmp;
        }

        Iterator& operator--() 
        {
            if (!m_node) 
            {
                if (!m_parent || !m_parent->m_tail)
                    throw std::out_of_range("Decrementing invalid iterator");
                m_node = m_parent->m_tail;
            }
            else 
            {
                m_node = m_node->prev;
                if (!m_node) 
                    throw std::out_of_range("Decrementing begin iterator");
            }
            return *this;
        }

        Iterator operator--(int) 
        {
            Iterator tmp = *this;
            --*this;
            return tmp;
        }

        node_type* get_node() const { return m_node; }

        const CStringList* get_parent() const { return m_parent; }

        template<bool OtherConst>
        bool operator==(const Iterator<OtherConst>& other) const 
        {
            return m_node == other.m_node;
        }

        template<bool OtherConst>
        bool operator!=(const Iterator<OtherConst>& other) const 
        {
            return !(*this == other);
        }
    };

    template <bool IsConst>
    class ReverseIterator 
    {
    private:
        using iterator_type = Iterator<IsConst>;
        iterator_type m_base;

    public:
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = typename iterator_type::value_type;
        using difference_type = typename iterator_type::difference_type;
        using pointer = typename iterator_type::pointer;
        using reference = typename iterator_type::reference;

        ReverseIterator() = default;
        explicit ReverseIterator(iterator_type it) : m_base(it) {}

        reference operator*() const 
        {
            auto tmp = m_base;
            --tmp;
            return *tmp;
        }

        pointer operator->() const { return m_base.operator->(); }

        ReverseIterator& operator++() 
        {
            --m_base;
            return *this;
        }

        ReverseIterator operator++(int) 
        {
            ReverseIterator tmp = *this;
            --m_base;
            return tmp;
        }

        ReverseIterator& operator--() 
        {
            ++m_base;
            return *this;
        }

        ReverseIterator operator--(int) 
        {
            ReverseIterator tmp = *this;
            ++m_base;
            return tmp;
        }

        bool operator==(const ReverseIterator& other) const { return m_base == other.m_base; }
        bool operator!=(const ReverseIterator& other) const { return !(*this == other); }
    };

    using iterator = Iterator<false>;
    using const_iterator = Iterator<true>;
    using reverse_iterator = ReverseIterator<false>;
    using const_reverse_iterator = ReverseIterator<true>;

    CStringList() = default;

    CStringList(const CStringList& other);

    CStringList(CStringList&& other) noexcept;

    CStringList(std::initializer_list<std::string> init);

    CStringList& operator=(const CStringList& other);

    CStringList& operator=(CStringList&& other) noexcept;

    ~CStringList() noexcept;

    void PushBack(const std::string& str);

    void PushBack(std::string&& str);

    void PushFront(const std::string& str);

    void PushFront(std::string&& str);

    iterator Insert(iterator pos, const std::string& str) 
    {
        return Insert(pos, std::string(str));
    }

    iterator Insert(iterator pos, std::string&& str) 
    {
        if (pos.get_parent() != nullptr && pos.get_parent() != this) 
        {
            throw std::invalid_argument("Iterator belongs to different container");
        }

        if (!pos.get_node()) 
        {
            PushBack(std::move(str));
            return iterator(m_tail);
        }

        auto new_node = std::make_unique<Node>(std::move(str));

        if (pos == begin()) 
        {
            PushFront(std::move(new_node));
            return begin();
        }
        else 
        {
            Node* pos_node = const_cast<Node*>(pos.get_node());
            new_node->prev = pos_node->prev;
            new_node->next = std::move(pos_node->prev->next);
            pos_node->prev = new_node.get();
            new_node->prev->next = std::move(new_node);
            ++m_size;
            return iterator(pos_node->prev);
        }
    }

    iterator Erase(iterator pos) 
    {
        if (pos.get_parent() != nullptr && pos.get_parent() != this)
        {
            throw std::invalid_argument("Iterator belongs to different container");
        }

        if (!pos.get_node()) 
        {
            throw std::out_of_range("Invalid iterator position");
        }

        Node* pos_node = const_cast<Node*>(pos.get_node());
        iterator next_it(pos_node->next.get());

        if (pos_node == m_head.get()) 
        {
            m_head = std::move(pos_node->next);
            if (m_head) 
            {
                m_head->prev = nullptr;
            }
            else 
            {
                m_tail = nullptr;
            }
        }
        else 
        {
            pos_node->prev->next = std::move(pos_node->next);
            if (pos_node->next) 
            {
                pos_node->next->prev = pos_node->prev;
            }
            else 
            {
                m_tail = pos_node->prev;
            }
        }

        --m_size;
        return next_it;
    }

    void Clear() noexcept;

    size_t GetSize() const noexcept 
    { 
        return m_size; 
    }

    bool IsEmpty() const noexcept 
    { 
        return m_size == 0; 
    }

    iterator begin() noexcept 
    { 
        return iterator(m_head.get()); 
    }

    const_iterator begin() const noexcept 
    { 
        return const_iterator(m_head.get()); 
    }

    const_iterator cbegin() const noexcept 
    { 
        return begin(); 
    }

    iterator end() noexcept 
    { 
        return iterator(nullptr, this); 
    }

    const_iterator end() const noexcept 
    { 
        return const_iterator(nullptr, this); 
    }

    const_iterator cend() const noexcept 
    { 
        return end(); 
    }

    reverse_iterator rbegin() noexcept { return reverse_iterator(end()); }

    const_reverse_iterator rbegin() const noexcept { return const_reverse_iterator(end()); }

    const_reverse_iterator crbegin() const noexcept { return rbegin(); }

    reverse_iterator rend() noexcept { return reverse_iterator(begin()); }

    const_reverse_iterator rend() const noexcept { return const_reverse_iterator(begin()); }

    const_reverse_iterator crend() const noexcept { return rend(); }

    void Swap(CStringList& other) noexcept;
};