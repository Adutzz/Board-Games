#include <stdio.h>
#define MAX 10000
int main(void)
{   //in vectorul H am adaugat valorile de heal, in S cele de shield
	//(folosesc nrh, respectiv nrs pentru a parcurge vectorii)
	//iar in Dmg atacul fiecarui inamic.
	unsigned int valoare = 0, S[MAX] = {0};
	int nrs = -1;
	int N = 0, M = 0;
	long HP;
	char tip;
	scanf("%ld%u", &HP, &N);
	for (int i = 0; i < N; i++) {
		scanf(" %c%u", &tip, &valoare);
			if (tip == 'H')
				HP += valoare;
			else if (tip == 'S')
				S[++nrs] = valoare;
			else
				printf("Invalid item type.\n");
	}
	//printf("Initial health points: %u\n",HP);

	//sortez vectorul de shield-uri
	for (int i = 0; i < nrs; i++)
		for (int j = i + 1; j <= nrs; j++) {
			if (S[j] < S[i]) {
				int aux = S[i];
				S[i] = S[j];
				S[j] = aux;
			}
		}
	scanf("%u", &M);
	for (int i = 0; i < M; i++) {
		long dmg = 0, sh = 0;
		//Inamicii
		scanf("%ld", &dmg);
		if (i == 0) {
			printf("Initial health points: %ld\n", HP);
		}
		//caut ce shield sa folosesc
		for (int j = 0; j <= nrs; j++) {
			if (nrs == 0) {
				sh = S[0];
				nrs--;
			} else if (((S[j] <= dmg) && (S[j + 1] > dmg)) ||
			((S[j] <= dmg) && (j == nrs)) || (S[0] >= dmg)) {
				sh = S[j];//shield-ul pe care il voi folosi
				for (int k = j; k < nrs; k++) { //sterg shieldul folosit
					S[k] = S[k + 1];        //din vectorul de shield-uri
				}
				nrs--;
				break;//daca am gasit shieldul potrivit, nu mai caut
			}
		}
			//folosesc shieldul
		if (dmg >= sh) {
			HP += sh - dmg;
		}
		if (HP <= 0)
			HP = 0;

		if (sh != 0)
			printf("%ld %ld\n", HP, sh);
		else
			printf("%ld\n", HP);
		if (HP == 0) {
			printf("You died.\n");
			break;
		}
	}
	if (HP != 0)
		printf("Foe Vanquished!\n");

	return 0;
}
