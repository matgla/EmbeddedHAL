import unittest

from utils.human_readable_size_parser import parse_size, to_kilobytes

class Test(unittest.TestCase):
    def test_conversion(self):
        self.assertEqual(parse_size("1500B"), 1500)
        self.assertEqual(parse_size("10K"), 10240)
        self.assertEqual(parse_size("4M"), 4194304)
        self.assertEqual(parse_size("8G"), 8589934592)
        self.assertEqual(parse_size("5T"), 5497558138880)

        self.assertEqual(parse_size("123b"), 123)
        self.assertEqual(parse_size("2k"), 2048)
        self.assertEqual(parse_size("3m"), 3145728)
        self.assertEqual(parse_size("4g"), 4294967296)
        self.assertEqual(parse_size("5t"), 5497558138880)

        self.assertEqual(parse_size("1500 B"), 1500)
        self.assertEqual(parse_size("10 K"), 10240)
        self.assertEqual(parse_size("4 M"), 4194304)
        self.assertEqual(parse_size("8 G"), 8589934592)
        self.assertEqual(parse_size("5 T"), 5497558138880)

        self.assertEqual(parse_size("123 b"), 123)
        self.assertEqual(parse_size("2 k"), 2048)
        self.assertEqual(parse_size("3 m"), 3145728)
        self.assertEqual(parse_size("4 g"), 4294967296)
        self.assertEqual(parse_size("5 t"), 5497558138880)

        self.assertEqual(parse_size("2kb"), 2048)
        self.assertEqual(parse_size("3 mB"), 3145728)
        self.assertEqual(parse_size("4 GB"), 4294967296)
        self.assertEqual(parse_size("5 Tb"), 5497558138880)

        self.assertEqual(parse_size("0x600"), 0x600)


    def test_from_bytes_to_kilobytes(self):
        self.assertEqual(to_kilobytes(1024), "1K")
        self.assertEqual(to_kilobytes(124123124), "121213K")
        self.assertEqual(to_kilobytes(4096), "4K")

if __name__ == '__main__':
    unittest.main()
