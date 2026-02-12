#include <bits/stdc++.h>
#define PSZ 100
#define MAX_GEN 100

using namespace std;

default_random_engine generator(chrono::system_clock::now().time_since_epoch().count());

class Chromosome {
public:
    static int budget;
    static int num_channels;
    static vector<double> ROI;
    static vector<pair<double, double>> bounds;
    static double Pc;
    static double Pm;
    double m_spare;
    vector<double> genes;
    vector<pair<double, double>> m_bounds;

    Chromosome() {
        genes.resize(num_channels);
        m_bounds.resize(num_channels);
        double sum_lower_bounds = 0, cost = 0;
        for(int i = 0; i < num_channels; i++) sum_lower_bounds += bounds[i].first;
        for (int i = 0; i < num_channels; i++) {
            sum_lower_bounds -= bounds[i].first;
            double upper_bound = bounds[i].second;
            if(bounds[i].second == -1) upper_bound = budget - sum_lower_bounds - cost;
            upper_bound = min(upper_bound, budget - sum_lower_bounds - cost);
            uniform_real_distribution<double> distribution(bounds[i].first, upper_bound);
            genes[i] = distribution(generator);
            cost += genes[i];
            m_bounds[i] = {bounds[i].first, upper_bound};
        }
        m_spare = budget - cost;
    }

    void recalculateSpare() {
        double cost = 0;
        for(double &gene : genes) {
            cost += gene;
        }
        m_spare = budget - cost;
    }
};

int Chromosome::budget;
int Chromosome::num_channels;
vector<double> Chromosome::ROI;
vector<pair<double, double>> Chromosome::bounds;
double Chromosome::Pc;
double Chromosome::Pm;

double __cost(const Chromosome& chromosome) {
    double ret = 0;
    for(double gene: chromosome.genes) {
        ret += gene;
    }
    return ret;
}

double fitness(const Chromosome& chromosome) {
    double ret = 0;
    for(int i = 0; i < Chromosome::num_channels; i++) {
        ret += Chromosome::ROI[i] / 100 * chromosome.genes[i];
    }
    return ret;
}

double fitness(const vector<Chromosome> &population) {
    double ret = 0;
    for(const Chromosome& chromosome : population) {
        ret += fitness(chromosome);
    }
    return ret;
}

vector<Chromosome> tournamentSelection(vector<Chromosome>& population) {
    vector<Chromosome> mating_pool(population.size());

    uniform_int_distribution<int> distribution(0, population.size()-1);
    for(int i = 0; i < population.size(); i++) {
        int idx1 = distribution(generator),
            idx2 = distribution(generator);

        if(fitness(population[idx1]) > fitness(population[idx2]))
            mating_pool[i] = population[idx1];
        else
            mating_pool[i] = population[idx2];
    }

    return mating_pool;
}

vector<Chromosome> twoPointCrossover(vector<Chromosome> &mating_pool) {
    shuffle(mating_pool.begin(), mating_pool.end(), std::mt19937(std::random_device()()));
    vector<Chromosome> new_generation(mating_pool.size());

    uniform_real_distribution<double> distribution0(0, 1);
    uniform_int_distribution<int> distribution1(0, Chromosome::num_channels-1);
    for(int i = 0; i + 1 < mating_pool.size(); i += 2) {
        double probability = distribution0(generator);
        if(probability < Chromosome::Pc) {
            new_generation[i] = mating_pool[i];
            new_generation[i+1] = mating_pool[i+1];
            continue;
        }

        int idx1 = distribution1(generator);

        uniform_int_distribution<int> distribution2(idx1, Chromosome::num_channels);
        int idx2 = distribution2(generator);

        Chromosome  c1 = mating_pool[i],
                    c2 = mating_pool[i+1];

        for(int j = idx1; j < idx2; j++) {
            c1.genes[j] = mating_pool[i+1].genes[j];
            c2.genes[j] = mating_pool[i].genes[j];
        }

        if(__cost(c1) > Chromosome::budget) {
            if(__cost(c2) > Chromosome::budget) {
                c1 = mating_pool[i];
                c2 = mating_pool[i+1];
            } else c1 = c2;
        } else if(__cost(c2) > Chromosome::budget) c2 = c1;

        c1.recalculateSpare();
        c2.recalculateSpare();

        assert(c1.m_spare >= -0.0001);
        assert(c2.m_spare >= -0.0001);

        new_generation[i] = c1;
        new_generation[i + 1] = c2;
    }

    return new_generation;
}

void uniformMutation(vector<Chromosome> &population) {
    uniform_real_distribution<double> distribution0(0, 1);
    for(Chromosome &chromosome : population) {
        for(int i = 0; i < Chromosome::num_channels; i++) {
            double probability = distribution0(generator);
            if (probability > Chromosome::Pm) continue;

            double delta;
            double ri1 = distribution0(generator);
            if (ri1 <= 0.5) {
                delta = chromosome.genes[i] - chromosome.m_bounds[i].first;
                uniform_real_distribution<double> distribution1(0, delta);
                double ri2 = distribution1(generator);
                chromosome.genes[i] = chromosome.genes[i] - ri2;
                chromosome.m_spare += ri2;
            } else {
                delta = min(chromosome.m_bounds[i].second - chromosome.genes[i], chromosome.m_spare);
                uniform_real_distribution<double> distribution1(0, delta);
                double ri2 = distribution1(generator);
                chromosome.genes[i] = chromosome.genes[i] + ri2;
                chromosome.m_spare -= ri2;
            }
            assert(chromosome.m_spare >= -0.0001);
        }
    }
}

void nonUniformMutation(vector<Chromosome> &population, int generation) {
    int b = 3;
    uniform_real_distribution<double> distribution0(0, 1);
    for(Chromosome &chromosome : population) {
        for(int i = 0; i < Chromosome::num_channels; i++) {
            double probability = distribution0(generator);
            if (probability > Chromosome::Pm) continue;

            double y, delta;
            double ri1 = distribution0(generator);
            if (ri1 <= 0.5) {
                y = chromosome.genes[i] - chromosome.m_bounds[i].first;
                double ri2 = distribution0(generator);
                delta = y * (1-pow(ri2, pow(1-1.0*generation/MAX_GEN, b)));
                chromosome.genes[i] = chromosome.genes[i] - delta;
                chromosome.m_spare += delta;
            } else {
                y = min(chromosome.m_bounds[i].second - chromosome.genes[i], chromosome.m_spare);
                double ri2 = distribution0(generator);
                delta = y * (1-pow(ri2, pow(1-1.0*generation/MAX_GEN, b)));
                chromosome.genes[i] = chromosome.genes[i] + delta;
                chromosome.m_spare -= delta;
            }
        }
    }
}

void elitistReplacement(const vector<Chromosome>& mating_pool, vector<Chromosome>& new_generation) {
    uniform_int_distribution<int> distribution(0, PSZ);
    int k = distribution(generator);
    for(int i = 0; i < k; i++)
        new_generation[i] = mating_pool[i];
}

int main() {
    freopen("input.in", "r", stdin);
    freopen("output.in", "w", stdout);

    //input
    cin >> Chromosome::budget >> Chromosome::num_channels;
    Chromosome::ROI.resize(Chromosome::num_channels);
    Chromosome::bounds.resize(Chromosome::num_channels);

    map<int, string> channel_name;

    cin.ignore();
    for(int i = 0; i < Chromosome::num_channels; i++) {
        string line;
        getline(cin, line);
        string val;

        while(line.back() != ' ') {
            val += line.back();
            line.pop_back();
        }
        line.pop_back();

        reverse(val.begin(), val.end());
        channel_name[i] = line;
        Chromosome::ROI[i] = stod(val);
    }

    for(int i = 0; i < Chromosome::num_channels; i++) {
        string LB, UB;
        cin >> LB >> UB;
        double dlb = LB == "x" ?  0 : stod(LB);
        double dub = UB == "x" ? -1 : stod(UB);
        Chromosome::bounds[i] = {dlb, dub};
    }

    // Pc 0.4 -> 0.7
    uniform_real_distribution<double> PcGen(0.4, 0.7);
    Chromosome::Pc = PcGen(generator);
    // Pm 0.001 -> 0.1
    uniform_real_distribution<double> PmGen(0, 0.1);
    Chromosome::Pm = PmGen(generator);

    Chromosome bestOverAll;

    for(int i = 0; i < 20; i++) {
        vector<Chromosome> population(PSZ);
        for(int gen = 0; gen < MAX_GEN; gen++) {
            vector<Chromosome> mating_pool = tournamentSelection(population);
            vector<Chromosome> new_generation = twoPointCrossover(mating_pool);
            uniformMutation(new_generation);
            nonUniformMutation(new_generation, gen);
            elitistReplacement(mating_pool, new_generation);
            population = new_generation;
        }

        Chromosome best = population.front();
        for(int j = 1; j < PSZ; j++) {
            if(fitness(population[j]) > fitness(best))
                best = population[j];
            assert(population[j].m_spare >= -0.0001);
        }
        for(int j = 0; j < Chromosome::num_channels; j++) {
            cout << channel_name[j] << " -> " << best.genes[j] << "k\n";
        }
        cout << fitness(best) << "\n\n";

        if(fitness(best) > fitness(bestOverAll)) bestOverAll = best;
    }

    cout << "BEST OVER ALL\n";
    for(int j = 0; j < Chromosome::num_channels; j++) {
        cout << channel_name[j] << " -> " << bestOverAll.genes[j] << "k\n";
    }
    cout << fitness(bestOverAll) << "\n\n";
    return 0;
}
