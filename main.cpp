#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>

class solution {
  public:
    std::vector<int> minTotalSum(const std::vector<std::vector<int>> & tri) {
        std::vector<std::vector<size_t>> paths = getPaths(tri, std::vector<size_t>{0});
        std::vector<std::vector<int>> nums;
        for (auto & path : paths) {
            std::vector<int> vec;
            int count = 0;
            std::transform(path.begin(), path.end(), std::inserter(vec, vec.begin()),[&](size_t idx){
                return tri[count++][idx];
            });
            nums.push_back(vec);
            // std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>(std::cout, " "));
            // std::cout << std::endl;
        }

        auto it = std::min_element(nums.begin(), nums.end(),
                                   [](const std::vector<int> & v1, const std::vector<int> & v2){
                                       return std::accumulate(v1.begin(), v1.end(), 0) < std::accumulate(v2.begin(), v2.end(), 0);
                                   });
        std::copy(it->begin(), it->end(), std::ostream_iterator<int>(std::cout, " "));
        std::cout << std::endl;
        return *it;
    }

  private:
    std::vector<std::vector<size_t>> getPaths(const std::vector<std::vector<int>> & tri, const std::vector<size_t> & curr) {
        std::vector<std::vector<size_t>> result;
        if (curr.size() == tri.size())
            result.push_back(curr);
        else {
            std::vector<size_t> next{curr.back(), curr.back()+1};
            for (auto nx : next) {
                auto cpy = curr;
                cpy.push_back(nx);
                auto temp = getPaths(tri, cpy);
                std::copy(temp.begin(), temp.end(), std::inserter(result, result.end()));
            }
        }
        return result;
    }
};

int main() {
    std::vector<std::vector<int>> triangle{
        {2},
        {3,4},
        {6,5,7},
        {4,1,8,3}
    };
    solution soln;
    auto minPath = soln.minTotalSum(triangle);
}
