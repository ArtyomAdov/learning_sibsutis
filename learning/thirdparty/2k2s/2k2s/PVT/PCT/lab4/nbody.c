#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>
#include <omp.h>



struct particle { float x, y, z; };

const float G = 6.67e-11;



void calculate_forces(struct particle *p, struct particle *f, float *m, int n);
void move_particles(struct particle *p, struct particle *f, struct particle *v, float *m, int n, double dt);
void serial_nbody(int argc, const char *argv[]);
void calculate_forces_v1(struct particle *p, struct particle *f, float *m, int n, int stream);
void nbody_v1__1_kritical_section(int argc, const char *argv[], int stream);
void calculate_forces_v2(struct particle *p, struct particle *f, float *m, int n);
void move_particles_v2(struct particle *p, struct particle *f, struct particle *v, float *m, int n, double dt);
void nbody_v2__6_atimic_operation(int argc, const char *argv[], int stream);
void calculate_forces_v3(struct particle *p, struct particle *f, float *m, int n);
void nbody_v3__n_blokirovok(int argc, const char *argv[], int stream);
void calculate_forces_v4(struct particle *p, struct particle *f, float *m, int n);
void nbody_v4__no_blokirovki_and_izbitochnie_vichislenia(int argc, const char *argv[], int stream);
void calculate_forces_v5(struct particle *p, struct particle *f[], float *m, int n);
void move_particles_v5(struct particle *p, struct particle *f[], struct particle *v, float *m, int n, double dt);
void nbody_v5__no_blokirovki_and_local_xranenie_vector_F_in_everybody_thread(int argc, const char *argv[], int stream);










double wtime()
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return tv.tv_sec + tv.tv_usec * 1E-6;
}

void calculate_forces(struct particle *p, struct particle *f, float *m, int n)
{
	for (int i = 0; i < n - 1; i++) {
		for (int j = i + 1; j < n; j++) {
			float dist = sqrtf(powf(p[i].x - p[j].x, 2) + powf(p[i].y - p[j].y, 2) + powf(p[i].z - p[j].z, 2));
			float mag = (G * m[i] * m[j]) / powf(dist, 2);

			struct particle dir = {
				.x = p[j].x - p[i].x,
				.y = p[j].y - p[i].y,
				.z = p[j].z - p[i].z,
			};

			f[i].x += mag * dir.x / dist;
			f[i].y += mag * dir.y / dist;
			f[i].z += mag * dir.z / dist;
			f[j].x -= mag * dir.x / dist;
			f[j].y -= mag * dir.y / dist;
			f[j].z -= mag * dir.z / dist;
		}
	}
}

void move_particles(struct particle *p, struct particle *f, struct particle *v, float *m, int n, double dt)
{
	for (int i = 0; i < n; i++) {
		struct particle dv = {
			.x = f[i].x / m[i] * dt,
			.y = f[i].y / m[i] * dt,
			.z = f[i].z / m[i] * dt,
		};

		struct particle dp = {
			.x = (v[i].x + dv.x / 2) * dt,
			.y = (v[i].y + dv.y / 2) * dt,
			.z = (v[i].z + dv.z / 2) * dt,
		};

		v[i].x += dv.x;
		v[i].y += dv.y;
		v[i].z += dv.z;
		
		p[i].x += dp.x;
		p[i].y += dp.y;
		p[i].z += dp.z;
		
		f[i].x = f[i].y = f[i].z = 0;
	}
}

void serial_nbody(int argc, const char *argv[])
{
	double ttotal, tinit = 0, tforces = 0, tmove = 0;
	
	ttotal = wtime();

	int n = (argc > 1) ? atoi(argv[1]) : 10;
	// char *filename = (argc > 2) ? argv[2] : NULL;
	
	tinit = -wtime();

	struct particle *p = malloc(sizeof(*p) * n);
	struct particle *f = malloc(sizeof(*f) * n);
	struct particle *v = malloc(sizeof(*v) * n);
	float *m = malloc(sizeof(*m) * n);

	for (int i = 0; i < n; i++) {
		p[i].x = rand() / (float)RAND_MAX - 0.5;
		p[i].y = rand() / (float)RAND_MAX - 0.5;
		p[i].z = rand() / (float)RAND_MAX - 0.5;
		
		v[i].x = rand() / (float)RAND_MAX - 0.5;
		v[i].y = rand() / (float)RAND_MAX - 0.5;
		v[i].z = rand() / (float)RAND_MAX - 0.5;
		
		m[i] = rand() / (float)RAND_MAX * 10 + 0.01;
		
		f[i].x = f[i].y = f[i].z = 0;
	}

	tinit += wtime();
	
	double dt = 1e-5;
	for (double t = 0; t <= 1; t += dt) {
		tforces -= wtime();
		calculate_forces(p, f, m, n);
		tforces += wtime();
		
		tmove -= wtime();
		move_particles(p, f, v, m, n, dt);
		tmove += wtime();
	}

	ttotal = wtime() - ttotal;

	printf("# NBody (n=%d)\n", n);
	printf("# Elapsed time (sec):\tttotal %.6f\n", ttotal);
	printf("\t\t\ttinit %.6f\n", tinit);
	printf("\t\t\ttforces %.6f\n", tforces);
	printf("\t\t\ttmove %.6f\n", tmove);

	// if (filename) {
	// 	FILE *fout = fopen(filename, "w");

	// 	if (!fout) {
	// 		fprintf(stderr, "Can't save file\n");
	// 		exit(EXIT_FAILURE);
	// 	}

	// 	for (int i = 0; i < n; i++) {
	// 		fprintf(fout, "%15f %15f %15f\n", p[i].x, p[i].y, p[i].z);
	// 	}

	// 	fclose(fout);
	// }

	free(m);
	free(v);
	free(f);
	free(p);
}



void nbody_v1__1_kritical_section(int argc, const char *argv[], int stream)
{
	double ttotal, tinit = 0, tforces = 0, tmove = 0;
	
	ttotal = wtime();

	int n = (argc > 1) ? atoi(argv[1]) : 10;
	
	tinit = -wtime();

	struct particle *p = malloc(sizeof(*p) * n);
	struct particle *f = malloc(sizeof(*f) * n);
	struct particle *v = malloc(sizeof(*v) * n);
	float *m = malloc(sizeof(*m) * n);

	for (int i = 0; i < n; i++) {
		p[i].x = rand() / (float)RAND_MAX - 0.5;
		p[i].y = rand() / (float)RAND_MAX - 0.5;
		p[i].z = rand() / (float)RAND_MAX - 0.5;
		
		v[i].x = rand() / (float)RAND_MAX - 0.5;
		v[i].y = rand() / (float)RAND_MAX - 0.5;
		v[i].z = rand() / (float)RAND_MAX - 0.5;
		
		m[i] = rand() / (float)RAND_MAX * 10 + 0.01;
		
		f[i].x = f[i].y = f[i].z = 0;
	}

	tinit += wtime();
	
	double dt = 1e-5;
	for (double t = 0; t <= 1; t += dt) {
		tforces -= wtime();
		calculate_forces_v1(p, f, m, n, stream);
		tforces += wtime();
		
		tmove -= wtime();
		move_particles(p, f, v, m, n, dt);
		tmove += wtime();
	}

	ttotal = wtime() - ttotal;

	printf("# NBody_v1__1_kritical_section (n=%d)\n", n);
	printf("# Elapsed time (sec):\tttotal %.6f\n", ttotal);
	printf("\t\t\ttinit %.6f\n", tinit);
	printf("\t\t\ttforces %.6f\n", tforces);
	printf("\t\t\ttmove %.6f\n", tmove);

	free(m);
	free(v);
	free(f);
	free(p);
}
	void calculate_forces_v1(struct particle *p, struct particle *f, float *m, int n, int stream)
	{
		#pragma omp parallel for num_threads(stream)
		for (int i = 0; i < n - 1; i++) {
			for (int j = i + 1; j < n; j++) {
				float dist = sqrtf(powf(p[i].x - p[j].x, 2) + powf(p[i].y - p[j].y, 2) + powf(p[i].z - p[j].z, 2));
				float mag = (G * m[i] * m[j]) / powf(dist, 2);
				
				struct particle dir = {
					.x = p[j].x - p[i].x,
					.y = p[j].y - p[i].y,
					.z = p[j].z - p[i].z
				};
				
				#pragma omp critical
				{
					f[i].x += mag * dir.x / dist;
					f[i].y += mag * dir.y / dist;
					f[i].z += mag * dir.z / dist;
					
					f[j].x -= mag * dir.x / dist;
					f[j].y -= mag * dir.y / dist;
					f[j].z -= mag * dir.z / dist;
				}
			}
		}
	}

void nbody_v2__6_atimic_operation(int argc, const char *argv[], int stream)
{
	double ttotal, tinit = 0, tforces = 0, tmove = 0;
	
	ttotal = wtime();

	int n = (argc > 1) ? atoi(argv[1]) : 10;
	
	tinit = -wtime();

	struct particle *p = malloc(sizeof(*p) * n);
	struct particle *f = malloc(sizeof(*f) * n);
	struct particle *v = malloc(sizeof(*v) * n);
	float *m = malloc(sizeof(*m) * n);

	for (int i = 0; i < n; i++) {
		p[i].x = rand() / (float)RAND_MAX - 0.5;
		p[i].y = rand() / (float)RAND_MAX - 0.5;
		p[i].z = rand() / (float)RAND_MAX - 0.5;
		
		v[i].x = rand() / (float)RAND_MAX - 0.5;
		v[i].y = rand() / (float)RAND_MAX - 0.5;
		v[i].z = rand() / (float)RAND_MAX - 0.5;
		
		m[i] = rand() / (float)RAND_MAX * 10 + 0.01;
		
		f[i].x = f[i].y = f[i].z = 0;
	}

	tinit += wtime();
	
	double dt = 1e-5;
	#pragma omp parallel num_threads(stream)
	{
		for (double t = 0; t <= 1; t += dt) {
			calculate_forces_v2(p, f, m, n);

			#pragma omp barrier
			move_particles_v2(p, f, v, m, n, dt);

			#pragma omp barrier
		}
	}

	ttotal = wtime() - ttotal;

	printf("# NBody (n=%d)\n", n);
	printf("# Elapsed time (sec):\tttotal %.6f\n", ttotal);
	printf("\t\t\ttinit %.6f\n", tinit);
	printf("\t\t\ttforces %.6f\n", tforces);
	printf("\t\t\ttmove %.6f\n", tmove);

	free(m);
	free(v);
	free(f);
	free(p);
}
	void calculate_forces_v2(struct particle *p, struct particle *f, float *m, int n)
	{
		#pragma omp for schedule(dynamic, 4) nowait
		for (int i = 0; i < n - 1; i++) {
			for (int j = i + 1; j < n; j++) {
				float dist = sqrtf(powf(p[i].x - p[j].x, 2) + powf(p[i].y - p[j].y, 2) + powf(p[i].z - p[j].z, 2));
				float mag = (G * m[i] * m[j]) / powf(dist, 2);
				
				struct particle dir = {
					.x = p[j].x - p[i].x,
					.y = p[j].y - p[i].y,
					.z = p[j].z - p[i].z
				};

				#pragma omp atomic
				f[i].x += mag * dir.x / dist;
				#pragma omp atomic
				f[i].y += mag * dir.y / dist;
				#pragma omp atomic
				f[i].z += mag * dir.z / dist;
				#pragma omp atomic
				f[j].x -= mag * dir.x / dist;
				#pragma omp atomic
				f[j].y -= mag * dir.y / dist;
				#pragma omp atomic
				f[j].z -= mag * dir.z / dist;
			}
		}
	}

	void move_particles_v2(struct particle *p, struct particle *f, struct particle *v, float *m, int n, double dt)
	{
		#pragma omp for nowait
		for (int i = 0; i < n; i++) {
			struct particle dv = {
				.x = f[i].x / m[i] * dt,
				.y = f[i].y / m[i] * dt,
				.z = f[i].z / m[i] * dt,
			};

			struct particle dp = {
				.x = (v[i].x + dv.x / 2) * dt,
				.y = (v[i].y + dv.y / 2) * dt,
				.z = (v[i].z + dv.z / 2) * dt,
			};
			
			v[i].x += dv.x;
			v[i].y += dv.y;
			v[i].z += dv.z;
			
			p[i].x += dp.x;
			p[i].y += dp.y;
			p[i].z += dp.z;
			
			f[i].x = f[i].y = f[i].z = 0;
		}
	}

omp_lock_t *locks;



void nbody_v3__n_blokirovok(int argc, const char *argv[], int stream)
{
	double ttotal, tinit = 0, tforces = 0, tmove = 0;
	
	ttotal = wtime();

	int n = (argc > 1) ? atoi(argv[1]) : 10;
	
	tinit = -wtime();

	struct particle *p = malloc(sizeof(*p) * n);
	struct particle *f = malloc(sizeof(*f) * n);
	struct particle *v = malloc(sizeof(*v) * n);
	float *m = malloc(sizeof(*m) * n);

	for (int i = 0; i < n; i++) {
		p[i].x = rand() / (float)RAND_MAX - 0.5;
		p[i].y = rand() / (float)RAND_MAX - 0.5;
		p[i].z = rand() / (float)RAND_MAX - 0.5;
		
		v[i].x = rand() / (float)RAND_MAX - 0.5;
		v[i].y = rand() / (float)RAND_MAX - 0.5;
		v[i].z = rand() / (float)RAND_MAX - 0.5;
		
		m[i] = rand() / (float)RAND_MAX * 10 + 0.01;
		
		f[i].x = f[i].y = f[i].z = 0;
	}

	tinit += wtime();
	
	locks = malloc(sizeof(omp_lock_t) * n);
	for (int i = 0; i < n; i++)
		omp_init_lock(&locks[i]);

	double dt = 1e-5;
	#pragma omp parallel num_threads(stream)
	{
		for (double t = 0; t <= 1; t += dt) {
			calculate_forces_v3(p, f, m, n);

			#pragma omp barrier
			move_particles_v2(p, f, v, m, n, dt);

			#pragma omp barrier
		}
	}

	ttotal = wtime() - ttotal;

	printf("# NBody (n=%d)\n", n);
	printf("# Elapsed time (sec):\tttotal %.6f\n", ttotal);
	printf("\t\t\ttinit %.6f\n", tinit);
	printf("\t\t\ttforces %.6f\n", tforces);
	printf("\t\t\ttmove %.6f\n", tmove);

	free(locks);
	free(m);
	free(v);
	free(f);
	free(p);
}
	void calculate_forces_v3(struct particle *p, struct particle *f, float *m, int n)
	{
		#pragma omp for schedule(dynamic, 4) nowait
		for (int i = 0; i < n - 1; i++) {
			for (int j = i + 1; j < n; j++) {
				float dist = sqrtf(powf(p[i].x - p[j].x, 2) + powf(p[i].y - p[j].y, 2) + powf(p[i].z - p[j].z, 2));
				float mag = (G * m[i] * m[j]) / powf(dist, 2);
				
				struct particle dir = {
					.x = p[j].x - p[i].x,
					.y = p[j].y - p[i].y,
					.z = p[j].z - p[i].z
				};
				
				omp_set_lock(&locks[i]);
				f[i].x += mag * dir.x / dist;
				f[i].y += mag * dir.y / dist;
				f[i].z += mag * dir.z / dist;
				omp_unset_lock(&locks[i]);
				
				omp_set_lock(&locks[j]);
				f[j].x -= mag * dir.x / dist;
				f[j].y -= mag * dir.y / dist;
				f[j].z -= mag * dir.z / dist;
				omp_unset_lock(&locks[j]);
			}
		}
	}
void nbody_v4__no_blokirovki_and_izbitochnie_vichislenia(int argc, const char *argv[], int stream)
{
	double ttotal, tinit = 0, tforces = 0, tmove = 0;
	
	ttotal = wtime();

	int n = (argc > 1) ? atoi(argv[1]) : 10;
	
	tinit = -wtime();

	struct particle *p = malloc(sizeof(*p) * n);
	struct particle *f = malloc(sizeof(*f) * n);
	struct particle *v = malloc(sizeof(*v) * n);
	float *m = malloc(sizeof(*m) * n);

	for (int i = 0; i < n; i++) {
		p[i].x = rand() / (float)RAND_MAX - 0.5;
		p[i].y = rand() / (float)RAND_MAX - 0.5;
		p[i].z = rand() / (float)RAND_MAX - 0.5;
		
		v[i].x = rand() / (float)RAND_MAX - 0.5;
		v[i].y = rand() / (float)RAND_MAX - 0.5;
		v[i].z = rand() / (float)RAND_MAX - 0.5;
		
		m[i] = rand() / (float)RAND_MAX * 10 + 0.01;
		
		f[i].x = f[i].y = f[i].z = 0;
	}

	tinit += wtime();

	double dt = 1e-5;
	#pragma omp parallel num_threads(stream)
	{
		for (double t = 0; t <= 1; t += dt) {
			calculate_forces_v4(p, f, m, n);

			#pragma omp barrier
			move_particles_v2(p, f, v, m, n, dt);

			#pragma omp barrier
		}
	}

	ttotal = wtime() - ttotal;

	printf("# NBody_v4__no_blokirovki_and_izbitochnie_vichislenia (n=%d)\n", n);
	printf("# Elapsed time (sec):\tttotal %.6f\n", ttotal);
	printf("\t\t\ttinit %.6f\n", tinit);
	printf("\t\t\ttforces %.6f\n", tforces);
	printf("\t\t\ttmove %.6f\n", tmove);

	free(m);
	free(v);
	free(f);
	free(p);
}

	void calculate_forces_v4(struct particle *p, struct particle *f, float *m, int n)
	{
		#pragma omp for schedule(dynamic, 4) nowait
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (i == j)
					continue;

				float dist = sqrtf(powf(p[i].x - p[j].x, 2) + powf(p[i].y - p[j].y, 2) + powf(p[i].z - p[j].z, 2));
				float mag = (G * m[i] * m[j]) / powf(dist, 2);
				
				struct particle dir = {
					.x = p[j].x - p[i].x,
					.y = p[j].y - p[i].y,
					.z = p[j].z - p[i].z
				};
				
				f[i].x += mag * dir.x / dist;
				f[i].y += mag * dir.y / dist;
				f[i].z += mag * dir.z / dist;
			}
		}
	}



void nbody_v5__no_blokirovki_and_local_xranenie_vector_F_in_everybody_thread(int argc, const char *argv[], int stream)
{
	double ttotal, tinit = 0, tforces = 0, tmove = 0;
	
	ttotal = wtime();

	int n = (argc > 1) ? atoi(argv[1]) : 10;
	
	tinit = -wtime();

	struct particle *p = malloc(sizeof(*p) * n);
	
	struct particle *f[stream];
	for (int i = 0; i < stream; i++)
		f[i] = malloc(sizeof(struct particle) * n);
	
	struct particle *v = malloc(sizeof(*v) * n);
	float *m = malloc(sizeof(*m) * n);

	for (int i = 0; i < n; i++) {
		p[i].x = rand() / (float)RAND_MAX - 0.5;
		p[i].y = rand() / (float)RAND_MAX - 0.5;
		p[i].z = rand() / (float)RAND_MAX - 0.5;
		
		v[i].x = rand() / (float)RAND_MAX - 0.5;
		v[i].y = rand() / (float)RAND_MAX - 0.5;
		v[i].z = rand() / (float)RAND_MAX - 0.5;
		
		m[i] = rand() / (float)RAND_MAX * 10 + 0.01;
	}

	tinit += wtime();

	double dt = 1e-5;
	#pragma omp parallel num_threads(stream)
	{
		for (double t = 0; t <= 1; t += dt) {
			calculate_forces_v5(p, f, m, n);

			#pragma omp barrier
			move_particles_v5(p, f, v, m, n, dt);

			#pragma omp barrier
		}
	}

	ttotal = wtime() - ttotal;

	printf("# NBody_v5__no_blokirovki_and_local_xranenie_vector_F_in_everybody_thread (n=%d)\n", n);
	printf("# Elapsed time (sec):\tttotal %.6f\n", ttotal);
	printf("\t\t\ttinit %.6f\n", tinit);
	printf("\t\t\ttforces %.6f\n", tforces);
	printf("\t\t\ttmove %.6f\n", tmove);

	free(m);
	free(v);
	// free(f);
	free(p);
}
	void calculate_forces_v5(struct particle *p, struct particle *f[], float *m, int n)
	{
		int tid = omp_get_thread_num();
		int nthreads = omp_get_num_threads();
		// printf("%d\n", nthreads);
		for (int i = 0; i < n; i++) {
			f[tid][i].x = 0;
			f[tid][i].y = 0;
			f[tid][i].z = 0;
		}
		
		#pragma omp for schedule(dynamic, 8)
		for (int i = 0; i < n; i++) {
			for (int j = i + 1; j < n; j++) {
				float dist = sqrtf(powf(p[i].x - p[j].x, 2) + powf(p[i].y - p[j].y, 2) + powf(p[i].z - p[j].z, 2));
				float mag = (G * m[i] * m[j]) / powf(dist, 2);
				
				struct particle dir = {
					.x = p[j].x - p[i].x,
					.y = p[j].y - p[i].y,
					.z = p[j].z - p[i].z
				};
				
				f[tid][i].x += mag * dir.x / dist;
				f[tid][i].y += mag * dir.y / dist;
				f[tid][i].z += mag * dir.z / dist;
				f[tid][j].x -= mag * dir.x / dist;
				f[tid][j].y -= mag * dir.y / dist;
				f[tid][j].z -= mag * dir.z / dist;
			}
		}
				
		#pragma omp single // Суммарная сила будет хранится в первой строке – f[0][i]
		{
			for (int i = 0; i < n; i++) {
				for (int tid = 1; tid < nthreads; tid++) {
					f[0][i].x += f[tid][i].x;
					f[0][i].y += f[tid][i].y;
					f[0][i].z += f[tid][i].z;
				}
			}
		}
	}

	void move_particles_v5(struct particle *p, struct particle *f[], struct particle *v, float *m, int n, double dt)
	{
		#pragma omp for
		for (int i = 0; i < n; i++) {
			struct particle dv = {
				.x = f[0][i].x / m[i] * dt,
				.y = f[0][i].y / m[i] * dt,
				.z = f[0][i].z / m[i] * dt,
			};

			struct particle dp = {
				.x = (v[i].x + dv.x / 2) * dt,
				.y = (v[i].y + dv.y / 2) * dt,
				.z = (v[i].z + dv.z / 2) * dt,
			};

			v[i].x += dv.x;
			v[i].y += dv.y;
			v[i].z += dv.z;
			
			p[i].x += dp.x;
			p[i].y += dp.y;
			p[i].z += dp.z;
			
			//f[i].x = f[i].y = f[i].z = 0;
		}
	}
int main(int argc, char const *argv[])
{
	serial_nbody(argc, argv);
	for (int i = 2; i <= 4; i+=2) {
		printf("Stream: %d\n", i);

		nbody_v1__1_kritical_section(argc, argv, i);
		nbody_v2__6_atimic_operation(argc, argv, i);
		nbody_v3__n_blokirovok(argc, argv, i);
		nbody_v4__no_blokirovki_and_izbitochnie_vichislenia(argc, argv, i);
		nbody_v5__no_blokirovki_and_local_xranenie_vector_F_in_everybody_thread(argc, argv, i);


// Версия 1 -- одна критическая секция
// Версия 2 -- 6 атомарных операций
// Версия 3 -- n блокировок
// Версия 4 -- версия без блокировок с избыточными вычислениями
// Версия 5 -- версия без блокировок с локальным хранением вектора сил в каждом потоке
	}

	return 0;
}