#include <memory>
#include <ostream>
#include <vector>
#include <cassert>
#include <type_traits>


class object_t;

template <typename T>
void draw(const T& x, std::ostream& out, std::size_t position)
{
	out << std::string(position, ' ') << x << std::endl;
}

using document = std::vector<object_t>;
void draw(const document& x, std::ostream& out, std::size_t position);

using history = std::vector<document>;
void commit(history& x);
void undo(history& x);
document& current(history& x);


class object_t
{
public:
	template <typename T>
	explicit object_t(T x) : self_{ std::make_unique<model<T>>(std::move(x)) } {}

	object_t(const object_t& other) : self_{ other.self_->copy_() } {}
	object_t& operator=(const object_t& other) { return *this = object_t(other); }

	object_t(object_t&&) noexcept = default;
	object_t& operator=(object_t&&) noexcept = default;

	friend void draw(const object_t& x, std::ostream& out, std::size_t position)
	{
		x.self_->draw_(out, position);
	}

private:
	struct concept_t
	{
		virtual ~concept_t() = default;
		virtual std::unique_ptr<concept_t> copy_() const = 0;
		virtual void draw_(std::ostream&, std::size_t) const = 0;
	};

	template <typename T>
	struct model final : concept_t
	{
		explicit model(T x) : data_{ std::move(x) } {}

		model(const model&) = default;
		model& operator=(const model&) = default;

		model(model&&) noexcept = default;
		model& operator=(model&&) noexcept = default;

		std::unique_ptr<concept_t> copy_() const override
		{
			return std::make_unique<model>(*this);
		}
		void draw_(std::ostream& out, std::size_t position) const override
		{
			draw(data_, out, position);
		}

		T data_;
	};

	std::unique_ptr<concept_t> self_;
};

