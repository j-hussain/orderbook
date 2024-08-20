#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <limits>
#include <string>
#include <vector>
#include <numeric>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <memory>
#include <variant>
#include <optional>
#include <tuple>
#include <format>

#include "Orderbook.h"

enum class OrderType {
    FillAndKill,
    GoodTillCancel
};

enum class Side {
    Buy,
    Sell
};

using Price = std::int32_t; // price can be signed
using Quantity = std::uint32_t; // quantity can't be negative
using OrderID = std::uint64_t;

struct LevelInfo {
    // levels are made up of price and quantity
    Price price_;
    Quantity quantity_;

};

using LevelInfos = std::vector<LevelInfo>;

// encapsulate levelinfo obj to represent each side of orderbook
class OrderbookLevelInfos {
public:
    OrderbookLevelInfos(const LevelInfos& bids, const LevelInfos& asks):
        bids_ { bids },
        asks_ { asks }
    {}

    const LevelInfos& GetBids() const {return bids_;}
    const LevelInfos& GetAsks const {return asks_};

private:
    LevelInfos bids_;
    LevelInfos asks;
};

class Order {
public:
    Order(OrderType orderType, OrderID orderID, Side side, Price price, Quantity quantity):
        orderType_ {orderType},
        orderID_ {orderID},
        side_ {side},
        price_ {price},
        initialQuantity_ {quantity},
        remainingQuantity_ {quantity}
    {}

    OrderID GetOrderID const {return orderID_;}
    Side GetSide() const {return side_;}
    Price GetPrice() const {return price_;}
    OrderType GetOrderType const {return orderType_; }
    Quantity GetInitialQuantity() const {return initialQuantity_;}
    Quantity GetRemainingQuantity() const {return remainingQuantity_;}
    Quantity GetFilledQuantity() const {return GetInitialQuantity() - GetRemainingQuantity();}

    // When a trade happens, the lowest quantity between both orders is the quantity used between
    // both orders to prevent order overfilling
    void Fill(Quantity quantity) {
        if (quantity > GetRemainingQuantity()) {
            throw std::logic_error("Order ({}) cannot be filled for more than its remaining quantity", GetOrderID());
        }

        remainingQuantity -= quantity;

    }
private:
    OrderType orderType_;
    OrderID orderID_;
    Side side_;
    Price price_;
    Quantity initialQuantity_;
    Quantity remainingQuantity_;
};

// Because we're storing a single order in multiple DS's in our orderbook, ref semantics make things easier
using OrderPointer = std::shared_ptr<Order>;
// List gives iterator that can't be invalidated irrespective of list size - useful for identifying order location (bid or ask orderbook)
// Despite vectors being contiguous in memory, using a list is just easier.
using OrderPointers = std::list<OrderPointer>;

// create abstraction to make orders modifiable
class OrderModify {
public:
    OrderModify(OrderID orderID, Side side, Price price, Quantity quantity):
    orderID_ {orderID},
    price_ {price},
    side_ {side},
    quantity_ {quantity}
    {}

    OrderID GetOrderID const {return orderID_;}
    Price GetPrice const {return price_;}
    Side GetSide() const {return side_;}
    Quantity GetQuantity const {return quantity_;}



};
int main() {return 0;}
