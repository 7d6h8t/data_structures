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

    public:
        template <typename... types>
        requires(std::same_as<T, types> && ...)
        list(const types&... args) : head_(new Node(T())) {
            Node* prev = head_;
            ((link(prev, create_node(args)), prev = prev->next_), ...);
        }

        ~list() {
            Node* current = head_;
            while (current != nullptr) {
                Node* next = current->next_;
                delete current;
                current = next;
            }
        }

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
    };
} // namespace ds