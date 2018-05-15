import numpy as np
import bornagain as ba
from bornagain import nm


def get_delta():
    """
    Returns a delta coefficient for a layer.
    Absolute value is distributed log-uniformly over the interval from 1e-12 to 5e-4
    """
    return np.exp(np.random.uniform(np.log(1e-12), np.log(5e-4)))


def get_beta(delta):
    """
    Returns a beta coefficient for a layer.
    The value is distributed log-uniformly
    in the range [abs(delta) * 1e-8, abs(delta)]
    """
    max = np.log(np.abs(delta))
    min = np.log(np.abs(delta) * 1e-8)
    return np.exp(np.random.uniform(min, max))


def get_height(n_layers):
    """
    Returns uniformly distributed heights of layers in nanometers.
    Distribution interval is [0.1, 100]
    :param n_layers: number of intermediate layers
    :return: list of layer heights in nm
    """
    return [(0.1 + (100 - 0.1) * rand) * nm for rand in np.random.random(n_layers)]


def generate_sample_parameters():
    """
    :return: a dictionary with parameters of the sample
    """
    n_layers = np.random.randint(0, 101)  # number of intermediate layers in a sample
    #  creating reflectivity coefficients (delta, beta) for ambient, intermediate layers and the substrate
    refl_coefs = [[0, 0]] + [[val, get_beta(val)] for val in [get_delta() for i in range(n_layers + 1)]]
    #  generating layer heights
    heights = get_height(n_layers)



if __name__ == '__main__':
    generate_sample_parameters()
