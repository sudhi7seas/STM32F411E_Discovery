from setuptools import setup, find_packages

setup(
    name="stm32-test-suite",
    version="0.1",
    packages=find_packages(),
    install_requires=[
        'pyserial',
        'robotframework',
        # any other dependencies
    ],
)