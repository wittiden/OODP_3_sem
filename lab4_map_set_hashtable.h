#pragma once
//set & multiset
template<typename T>
class BinaryTree {
    class Node {
    public:
        T key;
        int count;
        Node* left;
        Node* right;

        Node(T key = T(), Node* left = nullptr, Node* right = nullptr) {
            this->key = key;
            this->left = left;
            this->right = right;
            this->count = 1;
        }
    };
    Node* root;

    void clear(Node* node) {
        if (node) {
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }

    bool contains(Node* node, const T& key) const {
        if (!node) return false;
        if (key == node->key) return true;
        return (key < node->key) ? contains(node->left, key) : contains(node->right, key);
    }

    Node* insert(Node* node, const T& key) {
        if (!node) return new Node(key);
        if (key < node->key) node->left = insert(node->left, key);
        else if (key > node->key) node->right = insert(node->right, key);
        else {
            node->count++;
        }
        return node;
    }

    Node* findMin(Node* node) {
        while (node && node->left) {
            node = node->left;
        }
        return node;
    }

    Node* erase(Node* node, const T& key) {
        if (!node) return nullptr;
        if (key < node->key) node->left = erase(node->left, key);
        else if (key > node->key) node->right = erase(node->right, key);
        else {
            if (!node->left && !node->right) {
                delete node;
                return nullptr;
            }
            else if (!node->left) {
                Node* temp = node->right;
                delete node;
                return temp;
            }
            else if (!node->right) {
                Node* temp = node->left;
                delete node;
                return temp;
            }
            else {
                Node* temp = findMin(node->right);
                node->key = temp->key;
                node->right = erase(node->right, temp->key);
            }
        }
        return node;
    }
    Node* multiset_erase(Node* node, const T& key) {
        if (!node) return nullptr;

        if (key < node->key) {
            node->left = multiset_erase(node->left, key);
        }
        else if (key > node->key) {
            node->right = multiset_erase(node->right, key);
        }
        else {
            if (node->count > 1) {
                node->count--;
                return node;
            }
            else {
                if (!node->left && !node->right) {
                    delete node;
                    return nullptr;
                }
                else if (!node->left) {
                    Node* temp = node->right;
                    delete node;
                    return temp;
                }
                else if (!node->right) {
                    Node* temp = node->left;
                    delete node;
                    return temp;
                }
                else {
                    Node* temp = findMin(node->right);
                    node->key = temp->key;
                    node->count = temp->count;
                    node->right = multiset_erase(node->right, temp->key);
                }
            }
        }
        return node;
    }
    void simplePrint(Node* node) const {
        if (!node) return;
        simplePrint(node->left);

        for (int i = 0; i < node->count; i++) {
            std::cout << node->key << " ";
        }
        simplePrint(node->right);
    }
    bool findElement(Node* node, const T& key) const {
        if (!node) return false;
        if (key == node->key) return true;
        return (key < node->key) ? findElement(node->left, key) : findElement(node->right, key);
    }

    void filterElements(Node* node, std::vector<T>& result, const T& min_val, const T& max_val) const {
        if (!node) return;

        if (node->key >= min_val) {
            filterElements(node->left, result, min_val, max_val);
        }

        if (node->key >= min_val && node->key <= max_val) {
            for (int i = 0; i < node->count; i++) {
                result.push_back(node->key);
            }
        }

        if (node->key <= max_val) {
            filterElements(node->right, result, min_val, max_val);
        }
    }

public:
    Node* GetRoot() const { return root; }

    BinaryTree() : root(nullptr) {}
    ~BinaryTree() { clear(root); }

    bool contains(const T& key) const {
        return contains(root, key);
    }

    void insert(const T& key) {
        root = insert(root, key);
    }
    void multiset_insert(const T& key) {
        root = insert(root, key);
    }
    bool erase(const T& key) {
        if (!contains(key)) return false;
        root = erase(root, key);
        return true;
    }
    bool multiset_erase(const T& key) {
        if (!contains(key)) return false;
        root = multiset_erase(root, key);
        return true;
    }
    bool empty() const {
        return root == nullptr;
    }
    void printTree() const {
        if (!root) return;
        simplePrint(root);
        std::cout << std::endl;
    }
    bool find(const T& key) const {
        return findElement(root, key);
    }
    std::vector<T> filterRange(const T& min_val, const T& max_val) const {
        std::vector<T> result;
        filterElements(root, result, min_val, max_val);
        return result;
    }
};

//map & multimap
template<typename K, typename V>
class BinaryTreeMap {
    class Node {
    public:
        K key;
        std::vector<V> values;
        Node* left;
        Node* right;

        Node(K key = K(), V value = V(), Node* left = nullptr, Node* right = nullptr) {
            this->key = key;
            this->values.push_back(value);
            this->left = left;
            this->right = right;
        }
    };
    Node* root;

    void clear(Node* node) {
        if (node) {
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }

    bool contains(Node* node, const K& key) const {
        if (!node) return false;
        if (key == node->key) return true;
        return (key < node->key) ? contains(node->left, key) : contains(node->right, key);
    }

    Node* insert(Node* node, const K& key, const V& value) {
        if (!node) return new Node(key, value);
        if (key < node->key) node->left = insert(node->left, key, value);
        else if (key > node->key) node->right = insert(node->right, key, value);
        else {
            node->values.push_back(value);
        }
        return node;
    }

    Node* findMin(Node* node) {
        while (node && node->left) {
            node = node->left;
        }
        return node;
    }

    Node* erase(Node* node, const K& key) {
        if (!node) return nullptr;
        if (key < node->key) node->left = erase(node->left, key);
        else if (key > node->key) node->right = erase(node->right, key);
        else {
            if (!node->left && !node->right) {
                delete node;
                return nullptr;
            }
            else if (!node->left) {
                Node* temp = node->right;
                delete node;
                return temp;
            }
            else if (!node->right) {
                Node* temp = node->left;
                delete node;
                return temp;
            }
            else {
                Node* temp = findMin(node->right);
                node->key = temp->key;
                node->values = temp->values;
                node->right = erase(node->right, temp->key);
            }
        }
        return node;
    }

    void inOrderPrint(Node* node) const {
        if (!node) return;
        inOrderPrint(node->left);

        for (size_t i = 0; i < node->values.size(); i++) {
            std::cout << node->key << " : " << node->values[i];
            if (node->values.size() > 1) {
                std::cout << " [" << (i + 1) << "/" << node->values.size() << "]";
            }
            std::cout << std::endl;
        }

        inOrderPrint(node->right);
    }

    Node* find(Node* node, const K& key) const {
        if (!node) return nullptr;
        if (key == node->key) return node;
        return (key < node->key) ? find(node->left, key) : find(node->right, key);
    }

    void filterByKeyRange(Node* node, std::vector<std::pair<K, V>>& result,
        const K& min_key, const K& max_key) const {
        if (!node) return;

        if (node->key >= min_key) {
            filterByKeyRange(node->left, result, min_key, max_key);
        }

        if (node->key >= min_key && node->key <= max_key) {
            for (const auto& value : node->values) {
                result.push_back({ node->key, value });
            }
        }
        if (node->key <= max_key) {
            filterByKeyRange(node->right, result, min_key, max_key);
        }
    }
public:
    BinaryTreeMap() : root(nullptr) {}
    ~BinaryTreeMap() { clear(root); }

    bool contains(const K& key) const {
        return contains(root, key);
    }

    void insert(const K& key, const V& value) {
        root = insert(root, key, value);
    }

    bool erase(const K& key) {
        if (!contains(key)) return false;
        root = erase(root, key);
        return true;
    }

    bool empty() const {
        return root == nullptr;
    }

    bool update(const K& key, const V& value) {
        Node* node = find(root, key);
        if (node) {
            node->values.clear();
            node->values.push_back(value);
            return true;
        }
        return false;
    }

    bool update(const K& key, const V& old_value, const V& new_value) {
        Node* node = find(root, key);
        if (node) {
            auto it = std::find(node->values.begin(), node->values.end(), old_value);
            if (it != node->values.end()) {
                *it = new_value;
                return true;
            }
        }
        return false;
    }

    void printMap() const {
        if (!root) {
            std::cout << "Map пустой!" << std::endl;
            return;
        }
        std::cout << "=== MAP (ключ : значение) ===" << std::endl;
        inOrderPrint(root);
    }

    void findAndPrint(const K& key) const {
        Node* node = find(root, key);
        if (node) {
            std::cout << "Найдено для ключа " << key << ":\n";
            for (size_t i = 0; i < node->values.size(); i++) {
                std::cout << "  " << key << " : " << node->values[i];
                if (node->values.size() > 1) {
                    std::cout << " [" << (i + 1) << "/" << node->values.size() << "]";
                }
                std::cout << std::endl;
            }
        }
        else {
            std::cout << "Ключ " << key << " не найден!" << std::endl;
        }
    }

    std::vector<std::pair<K, V>> filterByKeyRange(const K& min_key, const K& max_key) const {
        std::vector<std::pair<K, V>> result;
        filterByKeyRange(root, result, min_key, max_key);
        return result;
    }

    std::vector<K> findByValue(const V& value) const {
        std::vector<K> result;
        findByValue(root, value, result);
        return result;
    }

    int getCount(const K& key) const {
        Node* node = find(root, key);
        return node ? node->values.size() : 0;
    }

    int uniqueSize() const {
        return countNodes(root);
    }

private:
    int countNodes(Node* node) const {
        if (!node) return 0;
        return 1 + countNodes(node->left) + countNodes(node->right);
    }
};

enum Method { Division = 1, Multiplication = 2, Universal = 3 };
template<typename Key, typename Value>
class Node {
public:
    Key key;
    Value value;
    Node* next;
    Node(const Key& key, const Value& value) : key(key), value(value), next(nullptr) {}
};

//map_hashTable
template<typename Key, typename Value>
class unordered_map {
    static const int DEFAULT_SIZE = 1000;
    int table_size;
    Node<Key, Value>** table;
    std::vector<Key> keys;
    Method method;
    double A = 0.6180339887;
    int uni_a, uni_b;
    const int uni_p = 2147483647;
    int element_count = 0;

    int stringToInt(const std::string& s) const {
        int h = 0;
        for (int i = 0; i < (int)s.length(); i++) {
            h = h * 31 + (int)s[i];
        }
        return (h < 0) ? -h : h;
    }

    int hashDivision(const Key& key) const {
        return hashKey(key) % table_size;
    }

    int hashMultiplication(const Key& key) const {
        int k = hashKey(key);
        double goldHesh = k * A;
        double frac = goldHesh - (int)goldHesh;
        return (int)(frac * table_size);
    }

    int simpleRandom(int min, int max) const {
        return min + (std::rand() % (max - min + 1));
    }

    int hashUniversal(const Key& key) const {
        int k = hashKey(key);
        return ((uni_a * k + uni_b) % uni_p) % table_size;
    }

    int hashKey(const Key& key) const {
        if constexpr (std::is_same<Key, std::string>::value) {
            return stringToInt(key);
        }
        else {
            return (int)key;
        }
    }

    int getIndex(const Key& key) const {
        if (method == Division) return hashDivision(key);
        else if (method == Multiplication) return hashMultiplication(key);
        else return hashUniversal(key);
    }

public:
    unordered_map(Method m = Division) : method(m), table_size(DEFAULT_SIZE) {
        table = new Node<Key, Value>* [table_size];
        for (int i = 0; i < table_size; i++) {
            table[i] = nullptr;
        }
        if (method == Universal) {
            srand(time(NULL));
            uni_a = simpleRandom(1, uni_p - 1);
            uni_b = simpleRandom(0, uni_p - 1);
        }
    }

    ~unordered_map() {
        clear();
        delete[] table;
    }


    void insert(const Key& key, const Value& value) {
        int idx = getIndex(key);

        Node<Key, Value>* curr = table[idx];
        while (curr) {
            if (curr->key == key) {
                curr->value = value;
                return;
            }
            curr = curr->next;
        }
        Node<Key, Value>* newNode = new Node<Key, Value>(key, value);
        if (!table[idx]) {
            table[idx] = newNode;
        }
        else {
            Node<Key, Value>* temp = table[idx];
            while (temp->next) temp = temp->next;
            temp->next = newNode;
        }

        keys.push_back(key);
        element_count++;
    }
    Value& operator[](const Key& key) {
        int idx = getIndex(key);

        Node<Key, Value>* curr = table[idx];
        while (curr) {
            if (curr->key == key) {
                return curr->value;
            }
            curr = curr->next;
        }
        insert(key, Value());
        return find(key)->value;
    }

    Node<Key, Value>* find(const Key& key) {
        int idx = getIndex(key);
        Node<Key, Value>* curr = table[idx];
        while (curr) {
            if (curr->key == key) {
                return curr;
            }
            curr = curr->next;
        }
        return nullptr;
    }
    bool erase(const Key& key) {
        int idx = getIndex(key);
        Node<Key, Value>* curr = table[idx];
        Node<Key, Value>* prev = nullptr;

        while (curr) {
            if (curr->key == key) {
                if (prev) {
                    prev->next = curr->next;
                }
                else {
                    table[idx] = curr->next;
                }
                for (int i = 0; i < (int)keys.size(); i++) {
                    if (keys[i] == key) {
                        keys.erase(keys.begin() + i);
                        break;
                    }
                }

                delete curr;
                element_count--;
                return true;
            }
            prev = curr;
            curr = curr->next;
        }
        return false;
    }
    void clear() {
        for (int i = 0; i < table_size; i++) {
            Node<Key, Value>* curr = table[i];
            while (curr) {
                Node<Key, Value>* temp = curr;
                curr = curr->next;
                delete temp;
            }
            table[i] = nullptr;
        }
        keys.clear();
        element_count = 0;
    }

    bool empty() const {
        return element_count == 0;
    }
    int size() const {
        return element_count;
    }
    std::vector<Key> getKeys() const {
        return keys;
    }
    bool contains(const Key& key) const {
        int idx = getIndex(key);
        Node<Key, Value>* curr = table[idx];
        while (curr) {
            if (curr->key == key) {
                return true;
            }
            curr = curr->next;
        }
        return false;
    }
    void printTable() const {
        std::cout << "\nХЕШ-ТАБЛИЦА (метод ";
        if (method == Division) std::cout << "деления";
        else if (method == Multiplication) std::cout << "умножения";
        else std::cout << "универсальный";
        std::cout << "):\n";

        for (int i = 0; i < table_size; i++) {
            if (table[i]) {
                std::cout << i << ": ";
                Node<Key, Value>* curr = table[i];
                while (curr) {
                    std::cout << "[" << curr->key << " : " << curr->value << "]";
                    if (curr->next) std::cout << " -> ";
                    curr = curr->next;
                }
                std::cout << "\n";
            }
        }
    }
    void printAll() const {
        std::cout << "\nВСЕ ЭЛЕМЕНТЫ (" << element_count << "):\n";
        for (int i = 0; i < (int)keys.size(); i++) {
            int idx = getIndex(keys[i]);
            Node<Key, Value>* node = table[idx];
            while (node && node->key != keys[i]) {
                node = node->next;
            }
            if (node) {
                std::cout << i + 1 << ". " << keys[i] << " -> " << node->value
                    << " (индекс: " << idx << ")\n";
            }
        }
    }
};