#ifndef RRT_H
#define RRT_H
#include <vector>

template <class T, class U> class RRT {
  public:
    RRT(T root) { vertices_.push_back(root); };
    auto nearest(T p) -> int;
    auto add_vertex(int parent, T p, U action) -> int;

  private:
    std::vector<T> vertices_;
    std::vector<U> actions_;
    std::vector<int> parents_;
};

template <class T, class U> auto RRT<T, U>::nearest(T p) -> int {
    float distance = (p - vertices_[0]).norm();
    int idx = 0;
    for (int i = 1; i < vertices_.size(); i++) {
        float candidate_dist = (p - vertices_[i]).norm();
        if (candidate_dist < distance) {
            idx = i;
            distance = candidate_dist;
        };
    };
    return idx;
};

template <class T, class U>
auto RRT<T, U>::add_vertex(int parent, T p, U action) -> int {
    vertices_.push_back(p);
    parents_.push_back(parent);
    actions_.push_back(action);
    return vertices_.size() - 1;
};

#endif
