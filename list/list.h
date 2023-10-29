#include <concepts>

// forward declaration
namespace ds {
    template <typename T>
    class list;
}

namespace ds {
    template <typename T>
    class node {
        friend class list<T>;

    public:
        node() = default;
        node(const T& data) : data_(data), prev_(nullptr), next_(nullptr) {}
        ~node() = default;

    private:
        T data_;
        node<T>* prev_;
        node<T>* next_;
    };

    template <typename T>
    class list final {
    private:
        using Node = node<T>;
        using value_type = T;
        using size_type = std::size_t;

    public:
        template <typename... types>
        requires(std::same_as<T, types> && ...)
        list(const types&... args) : head_(new Node()), tail_(new Node()) {
            link(head_, tail_);

            Node* prev = head_;
            ((link(prev, create_node(args)), prev = prev->next_), ...);
            tail_->prev_ = prev;
        }

        ~list() {
            clear();
            if (head_ != nullptr)
                delete head_;

            if (tail_ != nullptr)
                delete tail_;
        }

    public:
        // element access
        T& front() noexcept {
            return head_->next_->data_;
        }

        const T& front() const noexcept {
            return head_->next_->data_;
        }

        T& back() noexcept {
            return tail_->prev_->data_;
        }

        const T& back() const noexcept {
            return tail_->prev_->data_;
        }

        // capaticy
        bool empty() const noexcept {
            return (head_->next_ == tail_) && (tail_->prev_ == head_);
        }

        size_type size() const noexcept {
            size_type node_count = 0;

            if (empty())
                return node_count;

            Node* current = head_->next_;
            while (current != nullptr) {
                ++node_count;
                current = current->next_;
            }

            return node_count;
        }

        // modifiers
        void clear() noexcept {
            Node* current = head_->next_;
            while (current != nullptr) {
                Node* next = current->next_;
                delete current;
                current = next;
            }

            link(head_, tail_);
        }

        void push_back(const T& data) {
            Node* new_node = create_node(data);
            link(tail_->prev_, new_node);
            tail_->prev_ = new_node;
        }

        void push_back(T&& data) {
            Node* new_node = create_node(data);
            link(tail_->prev_, new_node);
            tail_->prev_ = new_node;
        }

        void push_front(const T& data) {
            Node* new_node = create_node(data);
            link(new_node, head_->next_);
            head_->next_ = new_node;
        }

        void push_front(T&& data) {
            Node* new_node = create_node(data);
            link(new_node, head_->next_);
            head_->next_ = new_node;
        }

    private:
        Node* create_node(const T& data) {
            Node* new_node = new Node(data);
            return new_node;
        }

        void link(Node* a, Node* b) const noexcept {
            a->next_ = b;
            b->prev_ = a;
        }

    private:
        Node* head_;
        Node* tail_;
    };
} // namespace ds