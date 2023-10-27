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

    public:
        template <typename... types>
        requires(std::same_as<T, types> && ...)
        list(const types&... args) : head_(new Node()), tail_(new Node()) {
            Node* prev = head_;
            ((link(prev, create_node(args)), prev = prev->next_), ...);
            tail_->next_ = prev;
        }

        ~list() {
            Node* current = head_;
            while (current != nullptr) {
                Node* next = current->next_;
                delete current;
                current = next;
            }

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
            return tail_->next_->data_;
        }

        const T& back() const noexcept {
            return tail_->next_->data_;
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