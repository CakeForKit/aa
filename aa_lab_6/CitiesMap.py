import networkx as nx
import matplotlib.pyplot as plt

class CitiesMap:
    cities = list()
    matrix = list()

    def __init__(self, filename):
        with open(filename, encoding="utf-8") as f:
            self.cities = f.readline().split(',')[1:]
            self.cities = [elem.rstrip() for elem in self.cities]

            line = f.readline()
            while line != '':
                self.matrix.append(list(map(int, line.split(',')[1:])))
                line = f.readline()

    def __str__(self):
        text = ' '.join(self.cities) + '\n'
        for line in self.matrix:
            text += ' '.join(map(lambda x: f'{x:5.0f}', line)) + '\n'
        return text

    def __len__(self):
        return len(self.cities)

    def __getitem__(self, item):
        return self.matrix[item]

    def draw(self, indexes=False, show=True):
        if indexes:
            cities = [i for i in range(len(self.cities))]
        else:
            cities = self.cities
        G = nx.Graph()
        for elem in cities:
            G.add_node(elem)
        for i in range(len(cities)):
            for j in range(i + 1, len(cities)):
                if self.matrix[i][j]:
                    G.add_edge(cities[i], cities[j], weight=self.matrix[i][j])
        plt.figure(figsize=(9, 6))
        plt.subplots_adjust(left=0.01, right=0.99, top=0.99, bottom=0.01)
        edges = [(u, v) for (u, v, d) in G.edges(data=True)]
        # pos = nx.spring_layout(G, seed=7)  # positions for all nodes - seed for reproducibility
        pos = nx.bfs_layout(G, (cities[0], cities[1]))
        nx.draw_networkx_nodes(G, pos, node_size=500, node_color='#fcaeae')
        nx.draw_networkx_edges(G, pos, edgelist=edges, width=1)
        nx.draw_networkx_labels(G, pos, font_size=11)
        edge_labels = nx.get_edge_attributes(G, "weight")
        nx.draw_networkx_edge_labels(G, pos, edge_labels, font_size=10)


        plt.savefig("img/path.png")
        if show:
            plt.show()