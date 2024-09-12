#include <iostream>
#include <vector>
#include <string>

// Enum untuk status pesanan
enum class OrderStatus {
    NotYetTaken,
    InKitchen,
    Served
};

// Kelas Order untuk menyimpan informasi pesanan
class Order {
public:
    Order(int id, const std::string& description)
        : id(id), description(description), status(OrderStatus::NotYetTaken) {}

    int getId() const { return id; }
    const std::string& getDescription() const { return description; }
    OrderStatus getStatus() const { return status; }
    void setStatus(OrderStatus newStatus) { status = newStatus; }

private:
    int id;
    std::string description;
    OrderStatus status;
};

// Kelas TableDisplay untuk menampilkan status pesanan
class TableDisplay {
public:
    void displayOrderTable(const std::vector<Order>& orders) {
        std::cout << "Order Table:\n";
        for (const auto& order : orders) {
            std::cout << "Order ID: " << order.getId() 
                      << ", Description: " << order.getDescription()
                      << ", Status: " << statusToString(order.getStatus()) << "\n";
        }
    }

private:
    std::string statusToString(OrderStatus status) const {
        switch (status) {
            case OrderStatus::NotYetTaken: return "Not Yet Taken";
            case OrderStatus::InKitchen: return "In Kitchen";
            case OrderStatus::Served: return "Served";
            default: return "Unknown";
        }
    }
};

// Kelas OrderManager untuk mengelola pesanan
class OrderManager {
public:
    void addOrder(const Order& order) {
        orders.push_back(order);
    }

    void updateOrderStatus(int id, OrderStatus newStatus) {
        for (auto& order : orders) {
            if (order.getId() == id) {
                order.setStatus(newStatus);
                return;
            }
        }
    }

    const std::vector<Order>& getOrders() const {
        return orders;
    }

private:
    std::vector<Order> orders;
};

int main() {
    OrderManager orderManager;
    TableDisplay tableDisplay;

    // Menambahkan beberapa pesanan
    orderManager.addOrder(Order(1, "Burger"));
    orderManager.addOrder(Order(2, "Pizza"));
    orderManager.addOrder(Order(3, "Pasta"));

    // Memperbarui status beberapa pesanan
    orderManager.updateOrderStatus(1, OrderStatus::InKitchen);
    orderManager.updateOrderStatus(2, OrderStatus::Served);

    // Menampilkan status pesanan
    tableDisplay.displayOrderTable(orderManager.getOrders());

    return 0;
}
