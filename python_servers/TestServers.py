import unittest
from exceptions import InvalidIDError, TooManyProductFoundError
from product import Product
from server import ListServer, MapServer, Client
from collections import Counter



class ProductTest(unittest.TestCase):

    def test_invalid_product_name(self):
        with self.assertRaises(InvalidIDError):
            Product('3r5d', 333.3)
        test_product = Product('abc33', 22)
        with self.assertRaises(InvalidIDError):
            test_product.name = 'cokolwiek'

    def test_ceate_product(self):
        self.assertTrue(isinstance(Product('abc4', 333), Product))

    def test_setter_product(self):
        test_product = Product('abc44', 333)
        self.assertEqual(test_product.name, 'abc44')
        self.assertEqual(test_product.price, 333)
        test_product.name = 'ab55'
        test_product.price = 222.22
        self.assertEqual(test_product.name, 'ab55')
        self.assertEqual(test_product.price, 222.22)


class ServerTest(unittest.TestCase):
    def test_create_list_server(self):
        self.assertTrue(isinstance(ListServer(), ListServer))

    def test_init_list_server_with_param(self):
        products = [Product('cc444', 4), Product('cds43', 5)]
        test_list_server = ListServer(products)
        self.assertTrue(isinstance(test_list_server, ListServer))
        self.assertEqual(Counter(products), Counter(test_list_server.catalog))

    def test_add_list(self):
        test_list_server = ListServer()
        p1 = Product('abc44', 222.3)
        p2 = Product('ab33', 17.23)
        test_list_server.catalog.append(p1)
        test_list_server.catalog.append(p2)
        self.assertEqual(test_list_server.catalog[0], p1)
        self.assertEqual(test_list_server.catalog[1], p2)

    def test_remove_list(self):
        test_list_server1 = ListServer()
        p1 = Product('abc33', 444.4)
        test_list_server1.catalog.append(p1)
        self.assertTrue(True, test_list_server1.remove_product('abc33'))
        self.assertEqual([], test_list_server1.catalog)

    def test_get_entries(self):
        test_list_server = ListServer()
        p1 = Product('abc44', 222.3)
        p2 = Product('ab33', 17.23)
        test_list_server.catalog.append(p1)
        test_list_server.catalog.append(p2)
        entries = test_list_server.get_entries(3)
        self.assertEqual(Counter([p1]), Counter(entries))

    def test_too_many_entries(self):
        test_products = list()
        for i in range(0, 17):
            test_products.append(Product('ccc33', i))
        test_list_server = ListServer(test_products)
        with self.assertRaises(TooManyProductFoundError):
            test_list_server.get_entries(3)

class ClientTest(unittest.TestCase):

    def test_client_map_server(self):
        map_server = MapServer()
        p1 = Product('abc44', 222.3)
        p2 = Product('ab33', 17.23)
        p3 = Product('abc33', 444.4)
        map_server.add(p1)
        map_server.add(p2)
        map_server.add(p3)
        test_client = Client(map_server)
        self.assertEqual(666.7, test_client.get_total_price(3))

    def test_client_list_server(self):
        list_server = ListServer()
        p1 = Product('abc44', 222.3)
        p2 = Product('ab33', 17.23)
        p3 = Product('abc33', 444.4)
        list_server.add(p1)
        list_server.add(p2)
        list_server.add(p3)
        test_client = Client(list_server)
        self.assertEqual(17.23, test_client.get_total_price(2))

    def test_client_empty_server(self):
        list_server = ListServer()
        test_client = Client(list_server)
        self.assertEqual(None, test_client.get_total_price(2))



if __name__ == "__main__":
    unittest.main()
