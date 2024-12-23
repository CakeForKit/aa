import networkx as nx
import matplotlib.pyplot as plt


def convert_path(x):
    # res = float(x) * 0.001
    # return res
    return float(x)

class CitiesMap:
    def __init__(self, filename):
        self.cities = list()
        self.matrix = list()
        with open(filename, encoding="utf-8") as f:
            self.cities = f.readline().split(',')[1:]
            self.cities = [elem.rstrip() for elem in self.cities]

            line = f.readline()
            while line != '':
                self.matrix.append(list(map(lambda x: convert_path(x), line.split(',')[1:])))  # Мм мегаметр
                line = f.readline()

        # print(f'matrix: {len(self.matrix)}x{len(self.matrix[0])}')
        self.day_pheromone = self.getDayPheromone()

    def attractiveness(self, i, j):
        if i == j:
            return 0
        return 1 / self.matrix[i][j]

    def getPath(self, inds):
        return [self.cities[i] for i in inds]

    def getLenPath(self, path):
        llen = 0
        for i in range(len(self.cities) - 1):
            llen += self.matrix[path[i]][path[i + 1]]
        llen += self.matrix[path[0]][path[-1]]
        return llen

    def getDayPheromone(self):
        day_pheromon = 0
        cnt = 0
        for i in range(len(self.matrix)):
            for j in range(len(self.matrix[0])):
                if i != j:
                    day_pheromon += self.matrix[i][j]
                    cnt += 1
        return day_pheromon / cnt

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

    def to_tex(self):
        text = ''
        for elem in self.matrix:
            text += ' & '.join(map(lambda x: f'{x:.0f}', elem)) + ' \\\\\n'
        return text