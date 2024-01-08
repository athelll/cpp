#ifndef CUSTOM_ARRAY_VIEW
#define CUSTOM_ARRAY_VIEW

template <typename T>
class s_array_view
{
private:
		T& m_array;

public:
		using Index = std::ptrdiff_t;

		s_array_view(T& array) : m_array { array } {}

		constexpr auto& operator[](Index index) {
				return m_array[static_cast<typename T::size_type>(index)];
		}
		constexpr const auto& operator[](Index index) const {
				return m_array[static_cast<typename T::size_type>(index)];
		}
		constexpr auto ssize() {
				return static_cast<Index>(m_array.size());
		}
};
#endif
