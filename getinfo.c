#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0


FILE* open_read_file(const char *filename) {
	FILE *fp;
	if ((fp = fopen(filename, "r")) == NULL) {
		printf("Error: Cannot open '%s' for reading\n",
			filename);
		return NULL;
	}
	return fp;
}


void print_cpu_info() {
	printf("Retreiving CPU information ...\n");
	FILE *fp;
	char buffer[80], *filename = "/proc/cpuinfo";

	if ((fp = open_read_file(filename)) == NULL) return;

	// Get line containing CPU model
	while (TRUE) {
		fgets (buffer, 80, fp);
		if (feof(fp) == TRUE) break;
		if (strstr(buffer, "model name")) {
			char *s = strstr(buffer, "model name");
			break;	
		
		}
	}

	// Display information
	if (feof(fp) != TRUE) {
		char *substring = strchr(buffer, ':');
		substring++;
		printf("CPU Model:%s", substring );
	}

	fclose(fp);
}


void print_kernel_info() {
	printf("Retreiving kernel information ...\n");
	FILE *fp;
	char buffer[80], *filename = "/proc/version";

	if ((fp = open_read_file(filename)) == NULL) return;

	// Get Linux version info then display
	fgets(buffer, 80, fp);
	printf("%s\n\n", buffer);
	fclose(fp);
}


void print_uptime_info() {
	printf("Retreiving uptime information ...\n");
	FILE *fp;
	char *filename = "/proc/uptime", buffer[80];

	if ((fp = open_read_file(filename)) == NULL) return;

	while (TRUE) {
		fgets(buffer, 80, fp);
		if (feof(fp) == TRUE) break;
		if (strstr(buffer, " ")) {
			char *s = strstr(buffer, " ");
			s = 0;
			break;	
		}
	}

	if (feof(fp) != TRUE) {
		unsigned short time = atoi(buffer);
		printf("Uptime: %u hrs %u mins %u seconds (%us)\n\n",
			(time/3600), ((time%3600)/60), (time%60), time);
	}

	fclose(fp);
}


void print_help_menu(void) {
	printf("\nUsage: cpuinfo -[c | k | u]\n");
	printf("\n  -c  --cpu\t Display CPU name and model");
	printf("\n  -k  --kernel\t Display kernel version and stats");
	printf("\n  -u  --uptime\t Display system uptime");
	printf("\n  -h  --help\t Display this menu\n\n");
}


unsigned short parse_args(char *argv[]) {
	if ((strcmp(argv[1], "-h") == 0) || 
		(strcmp(argv[1], "--help") == 0)) { print_help_menu(); }
	else if ((strcmp(argv[1], "-c") == 0) || 
		(strcmp(argv[1], "--cpu") == 0)) { print_cpu_info(); }
	else if ((strcmp(argv[1], "-k") == 0) || 
		(strcmp(argv[1], "--kernel") == 0)) { print_kernel_info(); }
	else if ((strcmp(argv[1], "-u") == 0) || 
		(strcmp(argv[1], "--uptime") == 0)) { print_uptime_info(); }
	else return -1;
	return 0;
}


int main(int argc, char *argv[]) {
	char **args = argv;
	// No arguments
	if ((argv[1] == NULL)) {
		printf("No arguments specified.");
		printf("\nSee cpuinf [-h | --help] for usage\n\n");
		return 0;

	}

	// Show arguments passed
	printf("Executing: %s [ ", argv[0]);
	while (*(args)++ && (*(args) != NULL)) printf("%s ", *args);
	printf("]\n");

	// Invalid argument checking
	if (parse_args(argv) != 0) {
		printf("\nInvalid argument [%s] given\n\n", argv[1]);
		return -1;
	}
	return 0;
}