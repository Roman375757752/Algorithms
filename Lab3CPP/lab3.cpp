#include <iostream>
#include <fstream>
#include <string>
#include "queue.h"
#include "vector.h"

using namespace std;

void bfs(int** graph, int num_vertices, int start, const string& filename) {
    Vector* distances = vector_create();
    vector_resize(distances, num_vertices);

    for (int i = 0; i < num_vertices; i++) {
        vector_set(distances, i, -1);
    }
    vector_set(distances, start, 0);

    Queue* queue = queue_create();
    queue_insert(queue, start);

    while (!queue_empty(queue)) {
        int current = queue_get(queue);
        queue_remove(queue);

        for (int i = 0; i < num_vertices; i++) {
            if (graph[current][i] == 1 && vector_get(distances, i) == -1) {
                vector_set(distances, i, vector_get(distances, current) + 1);
                queue_insert(queue, i);
            }
        }
    }

    ofstream output(filename);
    if (!output.is_open()) {
        cerr << "Ошибка: не удалось открыть файл " << filename << " для записи." << endl;
    } else {
        for (int i = 0; i < num_vertices; i++) {
            output << vector_get(distances, i) << endl;
        }
        output.close();
    }

    vector_delete(distances);
    queue_delete(queue);
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "usage: " << argv[0] << " <input_file> <output_file>" << endl;
        return 1;
    }

    ifstream input(argv[1]);
    if (!input.is_open()) {
        cerr << "Ошибка: не удалось открыть файл " << argv[1] << " для чтения." << endl;
        return 1;
    }

    int num_vertices;
    input >> num_vertices;

    int** graph = new int*[num_vertices];
    for (int i = 0; i < num_vertices; i++) {
        graph[i] = new int[num_vertices];
        for (int j = 0; j < num_vertices; j++) {
            input >> graph[i][j];
        }
    }
    input.close();

    bfs(graph, num_vertices, 0, argv[2]);

    for (int i = 0; i < num_vertices; i++) {
        delete[] graph[i];
    }
    delete[] graph;

    return 0;
}
