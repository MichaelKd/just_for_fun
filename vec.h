// small and very simple vector
template<typename T>
class vec {
public:
	explicit vec(size_t size = 0) :
		m_size(0),
		m_capacity(size),
		m_vec(nullptr) {

		if (size > 0)
			_alloc(size);
	}

	vec(const vec<T>& from) : vec(from.m_size) {
		std::copy(from.m_vec, from.m_vec + from.m_size, m_vec);
		m_size = from.m_size;
	}

	vec(const std::initializer_list<T> list) : vec(list.size()) {
		size_t index = 0;
		for (auto& item : list) {
			m_vec[index] = item;
			index += 1;
		}
		m_size = list.size();
	}
	
	vec(vec&& from) :
		m_size(from.m_size),
		m_capacity(from.m_capacity),
		m_vec(from.m_vec) {
		
		from.m_size = 0;
		from.m_capacity = 0;
		from.m_vec = nullptr;
	}

	T& operator=(const T& from) {
		if (&from == this) {
			return &this;
		}

		T* new_vec = new T[from.m_capacity];

		std::copy(from.m_vec, from.m_vec + from.m_size, new_vec);

		m_vec = new_vec;
		m_capacity = from.m_capacity;
		m_size = from.m_size;

		return &this;
	}
	
	vec<T>& operator=(const std::initializer_list<T>& list) { 	
	
		_alloc(list.size());
		
		for (auto& item : list) {
			push(item);
		}
	
		return *this;
	}
	
	vec<T>& operator=(vec<T>&& from){
		if (from == *this) {
			return &this;
		}
		
		m_size = from.m_size;
		m_capacity = from.m_capacity;
		m_vec = from.m_vec;
		
		from.m_size = 0;
		from.m_capacity = 0;
		from.m_vec = nullptr;
	}

	~vec() {
		if (m_vec != nullptr)
			delete[] m_vec;
	}

	void push(const T& value) {
		if (m_size >= m_capacity) {
			m_capacity += (m_capacity == 0) ? 1 : m_capacity * 1.5;
			_resize(m_capacity);
		}

		m_vec[m_size] = value;
		m_size += 1;
	}
	T pop() {
		m_size -= 1;
		return m_vec[m_size];
	}

	T& operator[](size_t index) {
		return m_vec[index];
	}

	const T& operator[](size_t index) const {
		return m_vec[index];
	}

	T* begin() {
		return m_vec;
	}

	T* end() {
		return m_vec + m_size;
	}

	size_t size() const {
		return m_size;
	}

	bool is_empty() const {
		return size() == 0;
	}
private:
	void _alloc(size_t new_size) {
		T* new_vec = new T[new_size];

		m_capacity = new_size;
		if (m_vec != nullptr)
			delete[] m_vec;

		m_vec = new_vec;
	}

	void _resize(size_t new_size) {
		T* new_vec = new T[new_size];

		if (m_vec != nullptr) {
			std::copy(m_vec, m_vec + m_size, new_vec);
			delete[] m_vec;
		}
		m_capacity = new_size;
		m_vec = new_vec;
	}
private:
	size_t m_size = 0;
	size_t m_capacity = 0;
	T* m_vec = nullptr;
};