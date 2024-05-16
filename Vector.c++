#pragma once
template <typename T>

class Vector
{
private:
    T *m_Data = nullptr;

    size_t m_Size = 0;
    size_t m_capacity = 0;

    void ReAlloc(size_t newCapacity)
    {
        // 1.allocate a new block of memory
        // 2. copy/move old elements into new block
        // 3. delete

        T *newBlock = (T*)::operator new(newCapacity*sizeof(T));
        if (newCapacity < m_Size)
        {
            m_Size = newCapacity;
        }


        for (size_t i = 0; i < m_Size; i++)
        {
            newBlock[i] = std::move(m_Data[i]);
        }
        for (size_t i = 0; i < m_Size; i++)
        {
            m_Data[i].~T();
        }

        ::operator delete(m_Data,m_capacity*sizeof(T));
        m_Data = newBlock;
        m_capacity = newCapacity;
    }

public:
    // for normal l value

    Vector()
    {

        // allocate 2 elements
        ReAlloc(2);
    }
    ~Vector()
    {
        Clear();
        ::operator delete(m_Data,m_capacity*sizeof(T));
    }
    void Pushback(const T &value)
    {

        if ((m_Size >= m_capacity))
        {
            ReAlloc(m_capacity + m_capacity / 2);
        }

        m_Data[m_Size] = value;
        m_Size++;
    }
    // for temporary value
    void Pushback(T &&value)
    {

        if ((m_Size >= m_capacity))
        {
            ReAlloc(m_capacity + m_capacity / 2);
        }

        m_Data[m_Size] = std::move(value);
        m_Size++;
    }
    // emplace back
    template <typename... Args>
    T &EmplaceBack(Args &&...args)
    {

        if ((m_Size >= m_capacity))
        {
            ReAlloc(m_capacity + m_capacity / 2);
        }

        new(&m_Data[m_Size]) T(std::forward<Args>(args)...);
        return m_Data[m_Size++];
    }
    void PopBack(){
        if(m_Size > 0){
            m_Size--;
            m_Data[m_Size].~T();
        }
    }
    void Clear(){
        for (size_t i = 0; i < m_Size; i++)
        {
            m_Data[i].~T();
        }
        m_Size=0;
    }
    const T &operator[](size_t index) const
    {
        if (index >= m_Size)
        {
            // assert
        }

        return m_Data[index];
    }
    T &operator[](size_t index)
    {
        if (index >= m_Size)
        {
            // assert
        }
        return m_Data[index];
    }

    size_t Size() const { return m_Size; }
};