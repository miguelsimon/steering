#ifndef RRT_H
#define RRT_H
#include <random>
#include <vector>

template <class T, class U> class RRTProblem {
  public:
    virtual auto random_state() -> T = 0;
    virtual auto plan(T src, T dst) -> std::tuple<bool, T, U> = 0;
};

template <class T, class U> class RRT {
  public:
    RRT(T root) { vertices_.push_back(root); };
    auto nearest(T p) -> int;
    auto get_vertex(int i) -> T;
    auto add_vertex(int parent, T p, U action) -> int;
    void step(RRTProblem<T, U> &problem);

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

template <class T, class U> auto RRT<T, U>::get_vertex(int idx) -> T {
    return vertices_[idx];
};

template <class T, class U>
auto RRT<T, U>::add_vertex(int parent, T p, U action) -> int {
    vertices_.push_back(p);
    parents_.push_back(parent);
    actions_.push_back(action);
    return vertices_.size() - 1;
};

template <class T, class U> void RRT<T, U>::step(RRTProblem<T, U> &problem) {
    T x_rand = problem.random_state();
    int x_near_idx = nearest(x_rand);
    T x_near = get_vertex(x_near_idx);

    auto [success, x_new, action] = problem.plan(x_near, x_rand);
    if (!success) {
        return;
    } else {
        add_vertex(x_near_idx, x_new, action);
    };
};

#endif
