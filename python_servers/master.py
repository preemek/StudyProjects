from product import Product
from server import ListServer

new_prod = Product('3adf', 333.3)
new_prod.name = '33rt'

test_list_server = ListServer()
p1 = Product('abc33', 444.4)
test_list_server.catalog.append(p1)
test_list_server.remove_product('abc33')
test_server_2 = ListServer()
