https://chatgpt.com/share/67706702-a5d4-8003-b633-4a81478642b8

https://leetcode.com/discuss/interview-question/5782507/Google-L4-or-Accepted-or-HyderabadPune

// A class to represent a single sell order
class Order {
public:
    long long order_id;   // Unique ID for this order
    int seller_id;        // Seller who placed this order
    long long price;      // Selling price
    long long timestamp;  // Timestamp to break ties

    // Constructor
    Order(long long oid, int sid, long long p, long long t)
        : order_id(oid), seller_id(sid), price(p), timestamp(t) {}

    // You could add any necessary member functions here
};

// Comparator class for the min-heap.
// It compares two orders based on price first, then timestamp.
class CompareOrders {
public:
    bool operator()(const Order &a, const Order &b) const {
        if (a.price == b.price) {
            // If the prices are the same, the order with the earlier (smaller) timestamp
            // should be at the top of the min-heap.
            return a.timestamp > b.timestamp;
        }
        // If prices differ, the order with the lower price should be at the top.
        return a.price > b.price;
    }
};

// A class that manages all sell orders for product "ABC"
class SellOrderBook {
private:
    // A priority queue (min-heap) of Orders, using CompareOrders for ordering.
    priority_queue<Order, vector<Order>, CompareOrders> minHeap;

    // Map seller_id -> the current active order_id for this seller
    unordered_map<int, long long> activeOrderOfSeller;

    // A global counter to assign unique IDs to new orders
    long long nextOrderID;

public:
    // Constructor
    SellOrderBook() : nextOrderID(1) {}

    // Creates or updates a sell order from a given seller with O(log N)
    void SellOrder(int seller_id, long long price, long long timestamp) {
        // Create a new order with a unique ID
        long long currentOrderID = nextOrderID++;
        Order newOrder(currentOrderID, seller_id, price, timestamp);

        // Mark this new order as active for the seller
        activeOrderOfSeller[seller_id] = currentOrderID;

        // Push it into the min-heap
        minHeap.push(newOrder);
    }

    // Retrieves (and removes) the cheapest valid order (earliest if tie) in O(log N) amortized
    Order BuyOrder() {
        while (!minHeap.empty()) {
            Order topOrder = minHeap.top();
            minHeap.pop();

            // Check if the top order is still active for its seller
            if (activeOrderOfSeller[topOrder.seller_id] == topOrder.order_id) {
                // It's valid, so mark it inactive
                activeOrderOfSeller[topOrder.seller_id] = 0; // or remove from map
                return topOrder;
            }
            // If not valid, continue popping
        }

        // If no valid order remains, return a sentinel order or handle accordingly
        return Order(-1, -1, -1, -1); 
    }
};
