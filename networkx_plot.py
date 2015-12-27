#!/usr/bin/env python
# http://networkx.github.io/documentation/latest/examples/drawing/weighted_graph.html
" An example using Graph as a weighted network "
__author__ = """Aric Hagberg (hagberg@lanl.gov)"""
# revised it to DiGraph, and add node shapes...
# graph = nx.from_numpy_matrix(Matrix)
# add_weighted_edge_from ; Is this depreciated?

# https://groups.google.com/forum/#!topic/networkx-discuss/N82JIe_rZYc
# import numpy as np
# import networkx as nx
# A=np.matrix([[1,2],[3,0]])
# G=nx.from_numpy_matrix(A,create_using=nx.MultiDiGraph())
# G.edges(data=True)
# [(0, 0, {'weight': 1}), (0, 1, {'weight': 2}), (1, 0, {'weight': 3})]


import matplotlib.pyplot as plt
import networkx as nx

G=nx.DiGraph()

G.add_edge('a', 'b', weight=0.6)
G.add_edge('a', 'c', weight=0.2)
G.add_edge('c', 'd', weight=0.1)
G.add_edge('c', 'e', weight=0.7)
G.add_edge('c', 'f', weight=0.9)
G.add_edge('a', 'd', weight=0.3)

nlarge = ['a', 'c', 'd']
nsmall = ['b', 'e', 'f']
elarge = [(u, v) for (u, v, d) in G.edges(data=True) if d['weight'] > 0.5]
esmall = [(u, v) for (u, v, d) in G.edges(data=True) if d['weight'] <= 0.5]

pos = nx.spring_layout(G) # positions for all nodes

# nodes
nx.draw_networkx_nodes(G, pos, nodelist = nlarge, node_size = 900, node_color = 'y')
nx.draw_networkx_nodes(G, pos, nodelist = nsmall, node_size = 600, node_color = 'g')

# edges
nx.draw_networkx_edges(G, pos, edgelist = elarge, width = 2)
nx.draw_networkx_edges(G, pos, edgelist = esmall, width = 2, alpha = 0.5, edge_color = 'b', style = 'dashed')

# labels
nx.draw_networkx_labels(G, pos, font_size = 20, font_family = 'sans-serif')

plt.axis('off')
plt.savefig("weighted_graph.png") # save as png
plt.show() # display
