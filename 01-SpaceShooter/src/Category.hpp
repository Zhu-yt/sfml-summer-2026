#ifndef CATEGORY_HPP
#define CATEGORY_HPP

namespace Category{
    enum type{
        None = 0,
        PlayerAircraft = 1 << 0,
        EnemyAircraft = 1 << 1,
        Aircraft = PlayerAircraft | EnemyAircraft,
    };
}

#endif //CATEGORY_HPP