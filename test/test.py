import sys
import os

current_directory = os.path.dirname(os.path.abspath(__file__))
module_directory = os.path.join(current_directory, '..')

sys.path.append(module_directory)

from signs import SignDatabase, Sign, Coordinates
import pytest

def test_add_find_sign():
    id_sign = 1
    name_sign = "Sign"
    coord_sign = Coordinates(12, 56.78)

    db = SignDatabase()

    sign = Sign()
    sign.id = id_sign
    sign.name = name_sign
    sign.coordinates = coord_sign

    db.add_sign(sign)

    assert db.find_sign(id_sign).id == id_sign
    assert db.find_sign(id_sign).name == name_sign

def test_add_duplicate_sign():
    id_sign = 1
    name_sign = "Sign"
    coord_sign = Coordinates(12, 56.78)

    db = SignDatabase()

    sign = Sign()
    sign.id = id_sign
    sign.name = name_sign
    sign.coordinates = coord_sign

    db.add_sign(sign)

    expected_msg_error = f"Sign with ID {id_sign} already exists."
    with pytest.raises(ValueError, match=expected_msg_error):
        db.add_sign(sign)

def test_find_nonexistent_sign(capfd):
    id_sign = 1

    db = SignDatabase()

    assert db.find_sign(id_sign) is None

    captured = capfd.readouterr()

    expected_msg = f"Sign with ID {id_sign} not found."
    assert expected_msg in captured.err

def test_remove_sign():
    id_sign = 1
    name_sign = "Sign"
    coord_sign = Coordinates(12, 56.78)

    db = SignDatabase()

    sign = Sign()
    sign.id = id_sign
    sign.name = name_sign
    sign.coordinates = coord_sign

    db.add_sign(sign)

    db.remove_sign(id_sign)

    assert db.find_sign(id_sign) is None

def test_remove_nonexistent_sign(capfd):
    id_sign = 1
    db = SignDatabase()

    db.remove_sign(id_sign)

    captured = capfd.readouterr()

    expected_msg = f"Sign with ID {id_sign} not found."
    assert expected_msg in captured.err

def test_add_multiple_signs():
    id_sign = 1
    name_prefix = "Sign"

    db = SignDatabase()

    signs = [Sign() for _ in range(3)]

    for sign in signs:
        sign.id = id_sign
        sign.name = name_prefix + str(id_sign)
        id_sign += 1

    db.add_signs(signs)

    id_sign = 1
    for _ in range(3):
        assert db.find_sign(id_sign).name == name_prefix + str(id_sign)

if __name__ == "__main__":
    pytest.main()