#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

#define NUM_PARTICLES 10000
#define MAX_ITERATIONS 50
#define DELTA_T 0.25
#define GAMMA 0.05

typedef struct {
    double a, b, c, d;     // Parameters
    double va, vb, vc, vd; // Velocities
    double error;          // Current error
    double best_error;     // Best error
    double best_a, best_b, best_c, best_d; // Best parameters
} Particle;

typedef struct {
    double a, b, c, d; // Global best parameters
    double error;      // Global best error
} GlobalBest;

// Function Prototypes
void initialize_particles(Particle *particles, int num_particles, double bounds[4][2], unsigned int seed_base);
double compute_error(Particle *particle, double target_x[], double target_y[], int time_steps);
void update_particles(Particle *particles, GlobalBest *global_best, double bounds[4][2], int num_particles, int thread_count, unsigned int seed_base);

int main(int argc, char *argv[]) {
    if (argc < 4) {
        fprintf(stderr, "Usage: %s <input_file> <num_threads> <seed> [p]\n", argv[0]);
        return 1;
    }

    // Read command-line arguments
    char *input_file = argv[1];
    int num_threads = atoi(argv[2]);
    unsigned int seed_base = atoi(argv[3]);
    int verbose = argc > 4 && argv[4][0] == 'p';

    // Read input file
    FILE *file = fopen(input_file, "r");
    if (!file) {
        perror("Error opening file");
        return 1;
    }

    double bounds[4][2]; // Bounds for a, b, c, d
    double true_params[4]; // True parameter values
    for (int i = 0; i < 4; i++) {
        if (fscanf(file, "%lf %lf %lf", &true_params[i], &bounds[i][0], &bounds[i][1]) != 3) {
            fprintf(stderr, "Error reading input file on line %d\n", i + 1);
            fclose(file);
            return 1;
        }
    }
    fclose(file);

    // Generate target time series
    double target_x[101], target_y[101];
    target_x[0] = 2.5;
    target_y[0] = 3.0;
    for (int t = 0; t < 100; t++) {
        target_x[t + 1] = target_x[t] + DELTA_T * (true_params[0] * target_x[t] - true_params[1] * target_x[t] * target_y[t]);
        target_y[t + 1] = target_y[t] + DELTA_T * (true_params[2] * target_x[t] * target_y[t] - true_params[3] * target_y[t]);
    }

    // Initialize particles and global best
    Particle *particles = malloc(sizeof(Particle) * NUM_PARTICLES);
    GlobalBest global_best = {0};
    global_best.error = INFINITY;
    initialize_particles(particles, NUM_PARTICLES, bounds, seed_base);

    // Array to track global best error for each iteration
    double global_errors[MAX_ITERATIONS + 1];

    // Main PSO loop
    double start_time = omp_get_wtime();
    for (int iter = 0; iter <= MAX_ITERATIONS; iter++) {
        #pragma omp parallel num_threads(num_threads)
        {
            int thread_id = omp_get_thread_num();
            unsigned int seed = seed_base + thread_id;

            #pragma omp for
            for (int i = 0; i < NUM_PARTICLES; i++) {
                particles[i].error = compute_error(&particles[i], target_x, target_y, 101);
                if (particles[i].error < particles[i].best_error) {
                    particles[i].best_error = particles[i].error;
                    particles[i].best_a = particles[i].a;
                    particles[i].best_b = particles[i].b;
                    particles[i].best_c = particles[i].c;
                    particles[i].best_d = particles[i].d;
                }

                #pragma omp critical
                {
                    if (particles[i].best_error < global_best.error) {
                        global_best.error = particles[i].best_error;
                        global_best.a = particles[i].best_a;
                        global_best.b = particles[i].best_b;
                        global_best.c = particles[i].best_c;
                        global_best.d = particles[i].best_d;
                    }
                }
            }
        }

        // Store the global best error for this iteration
        global_errors[iter] = global_best.error;

        // Update particles
        update_particles(particles, &global_best, bounds, NUM_PARTICLES, num_threads, seed_base);
    }
    double end_time = omp_get_wtime();

    // Output: Standard results
    printf("%.5f\n", global_best.error); // Line 1: Global error
    printf("%.5f %.5f %.5f %.5f\n", global_best.a, global_best.b, global_best.c, global_best.d); // Line 2: Parameters
    printf("%f\n", end_time - start_time); // Line 3: Execution time

    // Output: Verbose results (if 'p' is provided)
    if (verbose) {
        for (int i = 0; i <= MAX_ITERATIONS; i++) {
            printf("%.5f\n", global_errors[i]); // Line 4+: Iteration-wise errors
        }
    }

    free(particles);
    return 0;
}

// Function to initialize particles
void initialize_particles(Particle *particles, int num_particles, double bounds[4][2], unsigned int seed_base) {
    for (int i = 0; i < num_particles; i++) {
        unsigned int seed = seed_base + i;
        particles[i].a = bounds[0][0] + (rand_r(&seed) / (double)RAND_MAX) * (bounds[0][1] - bounds[0][0]);
        particles[i].b = bounds[1][0] + (rand_r(&seed) / (double)RAND_MAX) * (bounds[1][1] - bounds[1][0]);
        particles[i].c = bounds[2][0] + (rand_r(&seed) / (double)RAND_MAX) * (bounds[2][1] - bounds[2][0]);
        particles[i].d = bounds[3][0] + (rand_r(&seed) / (double)RAND_MAX) * (bounds[3][1] - bounds[3][0]);

        // Initialize small random velocities
        particles[i].va = ((rand_r(&seed) / (double)RAND_MAX) - 0.5) * 0.1;
        particles[i].vb = ((rand_r(&seed) / (double)RAND_MAX) - 0.5) * 0.1;
        particles[i].vc = ((rand_r(&seed) / (double)RAND_MAX) - 0.5) * 0.1;
        particles[i].vd = ((rand_r(&seed) / (double)RAND_MAX) - 0.5) * 0.1;

        particles[i].error = INFINITY;
        particles[i].best_error = INFINITY;
    }
}

// Function to compute error for a particle
double compute_error(Particle *particle, double target_x[], double target_y[], int time_steps) {
    double x = 2.5, y = 3.0;
    double total_error = 0.0;
    for (int t = 0; t < time_steps - 1; t++) {
        double next_x = x + DELTA_T * (particle->a * x - particle->b * x * y);
        double next_y = y + DELTA_T * (particle->c * x * y - particle->d * y);
        total_error += fabs(target_x[t + 1] - next_x) + fabs(target_y[t + 1] - next_y);
        x = next_x;
        y = next_y;
    }
    return total_error / time_steps; // Normalize by time steps
}

// Function to update particle positions and velocities
void update_particles(Particle *particles, GlobalBest *global_best, double bounds[4][2], int num_particles, int thread_count, unsigned int seed_base) {
    const double phi_l = 2.05, phi_g = 2.05, chi = 0.729;
    #pragma omp parallel for num_threads(thread_count)
    for (int i = 0; i < num_particles; i++) {
        unsigned int seed = seed_base + i;
        double rl = rand_r(&seed) / (double)RAND_MAX;
        double rg = rand_r(&seed) / (double)RAND_MAX;

        // Update velocities
        particles[i].va = chi * (particles[i].va + phi_l * rl * (particles[i].best_a - particles[i].a) + phi_g * rg * (global_best->a - particles[i].a));
        particles[i].vb = chi * (particles[i].vb + phi_l * rl * (particles[i].best_b - particles[i].b) + phi_g * rg * (global_best->b - particles[i].b));
        particles[i].vc = chi * (particles[i].vc + phi_l * rl * (particles[i].best_c - particles[i].c) + phi_g * rg * (global_best->c - particles[i].c));
        particles[i].vd = chi * (particles[i].vd + phi_l * rl * (particles[i].best_d - particles[i].d) + phi_g * rg * (global_best->d - particles[i].d));

        // Update positions
        particles[i].a += GAMMA * particles[i].va;
        particles[i].b += GAMMA * particles[i].vb;
        particles[i].c += GAMMA * particles[i].vc;
        particles[i].d += GAMMA * particles[i].vd;

        // Enforce bounds
        if (particles[i].a < bounds[0][0] || particles[i].a > bounds[0][1]) particles[i].a = bounds[0][0] + (rand_r(&seed) / (double)RAND_MAX) * (bounds[0][1] - bounds[0][0]);
        if (particles[i].b < bounds[1][0] || particles[i].b > bounds[1][1]) particles[i].b = bounds[1][0] + (rand_r(&seed) / (double)RAND_MAX) * (bounds[1][1] - bounds[1][0]);
        if (particles[i].c < bounds[2][0] || particles[i].c > bounds[2][1]) particles[i].c = bounds[2][0] + (rand_r(&seed) / (double)RAND_MAX) * (bounds[2][1] - bounds[2][0]);
        if (particles[i].d < bounds[3][0] || particles[i].d > bounds[3][1]) particles[i].d = bounds[3][0] + (rand_r(&seed) / (double)RAND_MAX) * (bounds[3][1] - bounds[3][0]);
    }
}
