#include <vector>
#include <boost/python.hpp>

template <class T, uint COST=1>
typename T::size_type dp(const T &a, const T &b)
{
    typedef typename T::size_type size_t;
    typedef std::vector<size_t> array_t;

    const T *min_str = (a.size() < b.size()) ? &a : &b,
            *max_str = (a.size() < b.size()) ? &b : &a;
    const size_t min_size = min_str->size(),
                 max_size = max_str->size();

    std::vector<array_t> states(2, array_t(min_size+1, 0));
    // initialize
    for (size_t i = 0; i < min_size+1; ++i) {
        states[0][i] = i;
    }

    for (size_t i = 1; i < max_size+1; ++i) {
        states[(i%2)][0] = i;
        for (size_t j = 1; j < min_size+1; ++j) {
            states[(i%2)][j] = std::min(std::min(states[!(i%2)][j], states[(i%2)][j-1])+1,
                                        states[!(i%2)][j-1]+((*max_str)[i-1] == (*min_str)[j-1] ? 0 : COST));
        }
    }

    return states[min_size%2][min_size];
}

unsigned int editdistance(const boost::python::object &a, const boost::python::object &b)
{
    const size_t size_a = boost::python::len(a),
                 size_b = boost::python::len(b);
    std::vector<int64_t> hashed_a(size_a, 0),
                         hashed_b(size_b, 0);

    for (size_t i = 0; i < size_a; ++i) {
        hashed_a[i] = PyObject_Hash(boost::python::object(a[i]).ptr());
    }
    for (size_t i = 0; i < size_b; ++i) {
        hashed_b[i] = PyObject_Hash(boost::python::object(b[i]).ptr());
    }

    return dp<std::vector<int64_t>, 2>(hashed_a, hashed_b);
}

BOOST_PYTHON_MODULE(__editdistance)
{
    boost::python::def("eval", &editdistance);
}
