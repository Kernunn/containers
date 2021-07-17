# containers
Re-implement c++ containers

### Usage
``make`` create ``prog``  
``./prog`` run all tests without additional output  
``make <container_name>[_print]`` runs tests for one container. If print is specified, then additional output will be displayed (example ``make vector_print``)

## Сontainer list
- [deque](/ft_containers/deque.hpp)
- [list](/ft_containers/list.hpp)
- [map](/ft_containers/map.hpp)
- [multimap](/ft_containers/multimap.hpp)
- [set](/ft_containers/set.hpp)
- [multiset](/ft_containers/multiset.hpp)
- [tree](/ft_containers/tree.hpp)
- [vector](/ft_containers/vector.hpp)
- [queue](/ft_containers/queue.hpp)
- [stack](/ft_containers/stack.hpp)
### Description
Each container is in ft namespace. Using ft::<container_name>.  
All methods from C++ 98 are implemented for all containers.  
All method prototypes, templates repeat the implementation of STL.  
Implemented allocator and reverse iterator class.  
Map, multimap, set, multiset based on Red Black Tree.  
Tree is the implementation of the Red Black tree.

  


