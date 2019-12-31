#include "fullsearch.hpp"

int full_search(const CitiesMap& distance)
{
    int n = distance.get_cities_number();
    vector<bool> visited(n, 0);
    vector<int> current_route;
    vector<int> min_route;
    int current_len = 0;
    int min_route_len = INT_MAX;
    for (int i = 0; i < n; i++)
    {
        current_route.clear();
        current_route.push_back(i);
        fill(visited.begin(), visited.end(), 0);
        visited[i] = 1;
        current_len = 0;
        hamilton(distance, min_route, min_route_len, current_route, visited, current_len);
    }
    return min_route_len;
}

void hamilton(const CitiesMap& distance, vector<int> &min_route, int &min_distance, vector<int> &current_route, vector<bool> &visited, int &current_len)
{
    if (current_route.size() == distance.get_cities_number())
    {
        s++;
        int tmp = distance.get_value(current_route.back(), current_route[0]);
        
        if (current_len + tmp < min_distance)
        {
            min_route = current_route;
            min_distance = current_len + tmp;
        }
        
        return;
    }
    for (int i = 0; i < distance.get_cities_number(); i++)
    {
        if (!visited[i])
        {
            int tmp = distance.get_value(current_route.back(), i);
            if (current_len + tmp > min_distance)
                continue;
            current_len += tmp;
            current_route.push_back(i);
            visited[i] = 1;
            hamilton(distance, min_route, min_distance, current_route, visited, current_len);
            visited[i] = 0;
            current_route.pop_back();
            current_len -= tmp;
        }
    }
}
