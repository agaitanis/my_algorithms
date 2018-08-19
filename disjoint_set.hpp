#ifndef DISJOINT_SET_HPP
#define DISJOINT_SET_HPP

#include <vector>

class DisjointSet {
        public:
                DisjointSet(int n);

                void merge(int i, int j);
                int find(int i);
                int get_size(int i);
        
        private:
                std::vector<int> parent;
                std::vector<int> ht;
                std::vector<int> sz;
};

#endif // DISJOINT_SET_HPP
