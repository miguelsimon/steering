#ifndef RRT_H
#define RRT_H
#include <functional>
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
    auto size() -> size_t { return vertices_.size(); };
    auto nearest(T p) -> int;
    auto get_vertex(size_t i) -> T;
    auto get_parent(size_t i) -> size_t;
    auto add_vertex(size_t parent, T p, U action) -> int;
    void step(RRTProblem<T, U> &problem);

    void visit(std::function<void(T src, T dst, U action)> f);
    void visit_path(size_t node, std::function<void(T src, T dst, U action)> f);

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

template <class T, class U> auto RRT<T, U>::get_vertex(size_t idx) -> T {
    return vertices_[idx];
};

template <class T, class U> auto RRT<T, U>::get_parent(size_t idx) -> size_t {
    assert(idx > 0);
    return parents_[idx - 1];
};

template <class T, class U>
auto RRT<T, U>::add_vertex(size_t parent, T p, U action) -> int {
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

template <class T, class U>
void RRT<T, U>::visit(std::function<void(T src, T dst, U action)> f) {
    for (size_t i = 0; i < parents_.size(); i++) {
        T dst = vertices_[i + 1];
        U action = actions_[i];
        T src = vertices_[parents_[i]];
        f(src, dst, action);
    };
};

template <class T, class U>
void RRT<T, U>::visit_path(size_t node,
                           std::function<void(T src, T dst, U action)> f) {

    // backtrack to start
    while (node != 0) {
        size_t parent_idx = parents_[node - 1];

        T dst = vertices_[node];
        T src = vertices_[parent_idx];
        U action = actions_[node - 1];

        f(src, dst, action);
        node = parent_idx;
    };
};

#endif
