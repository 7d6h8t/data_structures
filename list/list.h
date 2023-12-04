#include <compare>
#include <concepts>
#include <utility>

// forward declaration
namespace ds {
    template <typename T>
    class list;

    template <typename T>
    class list_iterator;

    template <typename T>
    class list_const_iterator;
} // namespace ds

namespace ds {
    template <typename T>
    class node {
        friend class list<T>;
        friend class list_iterator<T>;
        friend class list_const_iterator<T>;

    public:
        node() : prev_(this), next_(this) {}
        node(const T& value) : value_(value), prev_(nullptr), next_(nullptr) {}
        ~node() = default;

    private:
        T value_;
        node<T>* prev_;
        node<T>* next_;
    };

    template <typename T>
    class list_iterator {
    private:
        using Node = node<T>;
        using value_type = T;
        using reference = T&;
        using pointer = T*;
        using self = list_iterator<T>;

    public:
        list_iterator() : node_() {}
        list_iterator(Node* node) : node_(node) {}

    public:
        reference operator*() {
            return node_->value_;
        }

        pointer operator->() {
            return node_->next_;
        }

        self& operator++() {
            node_ = node_->next_;
            return *this;
        }

        self operator++(int) {
            self temp = *this;
            node_ = node_->next_;
            return temp;
        }

        self& operator--() {
            node_ = node_->prev_;
            return *this;
        }

        self operator--(int) {
            self temp = *this;
            node_ = node_->prev_;
            return temp;
        }

        bool operator==(const self& rhs) const {
            return node_ == rhs.node_;
        }

        bool operator!=(const self& rhs) const {
            return node_ != rhs.node_;
        }

    public:
        Node* node_;
    };

    template <typename T>
    class list_const_iterator {
    private:
        using Node = const node<T>;
        using value_type = T;
        using reference = const T&;
        using pointer = const T*;
        using self = list_const_iterator<T>;

    public:
        list_const_iterator() : node_() {}
        list_const_iterator(const Node* node) : node_(node) {}

    public:
        reference operator*() const {
            return node_->value_;
        }

        pointer operator->() const {
            return node_->next_;
        }

        self& operator++() {
            node_ = node_->next_;
            return *this;
        }

        self operator++(int) {
            self temp = *this;
            node_ = node_->next_;
            return temp;
        }

        self& operator--() {
            node_ = node_->prev_;
            return *this;
        }

        self operator--(int) {
            self temp = *this;
            node_ = node_->prev_;
            return temp;
        }

        bool operator==(const self& rhs) const {
            return node_ == rhs.node_;
        }

        bool operator!=(const self& rhs) const {
            return node_ != rhs.node_;
        }

    public:
        const Node* node_;
    };

    template <typename T>
    class list final {
    private:
        using Node = node<T>;

    public:
        using value_type = T;
        using size_type = std::size_t;
        using iterator = list_iterator<T>;
        using const_iterator = list_const_iterator<T>;

    public:
        template <typename... types>
        requires(std::same_as<T, types> && ...)
        list(const types&... args) : head_(new Node()), size_(0) {
            (push_back(args), ...);
        }

        ~list() {
            clear();

            if (head_.node_ != nullptr)
                delete head_.node_;
        }

    public:
        // element access
        T& front() noexcept {
            return *(begin());
        }

        const T& front() const noexcept {
            return *(begin());
        }

        T& back() noexcept {
            iterator temp = end();
            --temp;
            return *temp;
        }

        const T& back() const noexcept {
            iterator temp = end();
            --temp;
            return *temp;
        }

        // iterators
        iterator begin() noexcept {
            return iterator(head_.node_->next_);
        }

        const_iterator begin() const noexcept {
            return const_iterator(head_.node_->next_);
        }

        const_iterator cbegin() const noexcept {
            return const_iterator(head_.node_->next_);
        }

        iterator end() noexcept {
            return iterator(head_.node_);
        }

        const_iterator end() const noexcept {
            return const_iterator(head_.node_);
        }

        const_iterator cend() const noexcept {
            return const_iterator(head_.node_);
        }

        // capaticy
        bool empty() const noexcept {
            return size_ == 0;
        }

        size_type size() const noexcept {
            return size_;
        }

        // modifiers
        void clear() noexcept {
            iterator itr = begin();
            while (itr != end()) {
                Node* temp = itr.node_;
                ++itr;
                delete temp;
                --size_;
            }

            head_.node_->prev_ = head_.node_;
            head_.node_->next_ = head_.node_;
        }

        iterator insert(iterator pos, const T& value) {
            Node* new_node = create_node(value);
            Node* prev_node = pos.node_->prev_;

            link(new_node, pos.node_);
            link(prev_node, new_node);

            ++size_;
            return iterator(new_node);
        }

        iterator erase(iterator pos) {
            Node* prev_node = pos.node_->prev_;
            Node* next_node = pos.node_->next_;

            link(prev_node, next_node);

            delete pos.node_;

            --size_;
            return iterator(next_node);
        }

        void pop_back() {
            erase(end());
        }

        void pop_front() {
            erase(begin());
        }

        void push_back(const T& value) {
            insert(end(), value);
        }

        void push_back(T&& value) {
            insert(end(), std::move(value));
        }

        void push_front(const T& value) {
            insert(begin(), value);
        }

        void push_front(T&& value) {
            insert(begin(), std::move(value));
        }

    private:
        Node* create_node(const T& value) {
            Node* new_node = new Node(value);
            return new_node;
        }

        void link(Node* a, Node* b) const noexcept {
            if (a != nullptr)
                a->next_ = b;
            if (b != nullptr)
                b->prev_ = a;
        }

        void unlink(Node* a, Node* b) const noexcept {
            if (a != nullptr)
                a->next_ = nullptr;
            if (b != nullptr)
                b->prev_ = nullptr;
        }

    private:
        iterator head_;
        size_type size_;
    };

    template <typename T>
    bool operator==(const list<T>& a, const list<T>& b) {
        if (a.size() != b.size())
            return false;

        using const_iterator = list<T>::const_iterator;

        const_iterator itr_a = a.begin();
        const_iterator itr_b = b.begin();

        const_iterator a_end = a.end();
        const_iterator b_end = b.end();

        while (itr_a != a_end && itr_b != b_end && *itr_a == *itr_b) {
            ++itr_a;
            ++itr_b;
        }

        return (itr_a == a_end) && (itr_b == b_end);
    }

    template <typename T>
    std::weak_ordering operator<=>(const list<T>& lhs, const list<T>& rhs) {
        if (lhs.size() < rhs.size())
            return std::weak_ordering::less;

        if (lhs.size() > rhs.size())
            return std::weak_ordering::greater;

        auto lhs_itr = lhs.begin();
        auto rhs_itr = rhs.begin();

        while (lhs_itr != lhs.end()) {
            if (*lhs_itr < *rhs_itr)
                return std::weak_ordering::less;

            if (*lhs_itr > *rhs_itr)
                return std::weak_ordering::greater;

            ++lhs_itr;
            ++rhs_itr;
        }

        return std::weak_ordering::equivalent;
    }
} // namespace ds