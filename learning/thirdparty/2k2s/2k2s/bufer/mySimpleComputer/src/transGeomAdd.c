#include "transGeomAdd.h"

int g_lba2chs(tLBA lba_geom, tCHS *chs_geom)
{
	// tCHS best = {0, 0, 63};
	// for (uint16_t i = 0; i < 256; ++i) {
	// 	for (uint16_t j = 0; j < 1024; ++j) {
	// 		int64_t dif = (int64_t) (lba_geom) - 63 * i * j;
	// 		int64_t b_dif = (int64_t) (lba_geom) - 63 * best.c * best.h;
	// 		if (dif >= 0 && dif <= b_dif) {
	// 			best.h = (uint8_t) i;
	// 			best.c = j;
	// 		}
	// 	}
	// }
	// chs_geom->c = best.c;
	// chs_geom->h = best.h;
	// chs_geom->s = 63;

	tCHS geom = {0, 0, 63};
	int L1 = lba_geom / geom.s;
	// printf("%d\n", L1);

	int pow = 2;
	int L2 = L1 / 1023;
	while (pow < L2 && pow < 256)
		pow *= 2;
	
	// printf("%d\n", pow);

	if (pow == 256) {
		geom.h = (uint8_t) pow - 1;
	} else {
		geom.h = (uint8_t) pow;
	}

	geom.c = L1 / geom.h;

	chs_geom->c = geom.c;
	chs_geom->h = geom.h;
	chs_geom->s = geom.s;

    return 0;
}

int g_lba2large(tLBA lba_geom, tLARGE *large_geom)
{
	tCHS chs_geom;
	g_lba2chs(lba_geom, &chs_geom);
	g_chs2large(chs_geom, large_geom);
	return 0;
}

int g_lba2idechs(tLBA lba_geom, tIDECHS *idechs_geom)
{
	tIDECHS best = {0, 0, 255};
	for (uint16_t i = 0; i < 256; ++i) {
		for (uint32_t j = 0; j < UINT16_MAX; ++j) {
			int64_t dif = (int64_t) (lba_geom) - 255 * i * j;
			int64_t b_dif = (int64_t) (lba_geom) - 255 * best.c * best.h;
			if (dif >= 0 && dif <= b_dif) {
				best.h = (uint8_t) i;
				best.c = (uint16_t) j;
			}
		}
	}
	idechs_geom->c = best.c;
	idechs_geom->h = best.h;
	idechs_geom->s = 255;
	return 0;
}

int g_chs2large(tCHS chs_geom, tLARGE *large_geom)
{
	uint32_t pow = 2;
	large_geom->c = (uint16_t) (chs_geom.c / pow);
	large_geom->h = (uint8_t) (chs_geom.h * pow);
	large_geom->s = chs_geom.s;
	return 0;
}

int g_chs2lba(tCHS chs_geom, tLBA *lba_geom)
{
	*lba_geom = (uint32_t) (chs_geom.c * chs_geom.h * chs_geom.s);
	return 0;
}

int g_chs2idechs(tCHS chs_geometry, tIDECHS *idechs_geometry)
{
	tLBA lba_geom;
	g_chs2lba(chs_geometry, &lba_geom);
	g_lba2idechs(lba_geom, idechs_geometry);
	return 0;
}

int g_large2lba(tLARGE large_geometry, tLBA *lba_geometry)
{
	*lba_geometry = large_geometry.c * large_geometry.h * large_geometry.s;
	return 0;
}

int g_large2chs(tLARGE large_geometry, tCHS *chs_geometry)
{
	tLBA lba_geom;
	g_large2lba(large_geometry, &lba_geom);
	g_lba2chs(lba_geom, chs_geometry);
	return 0;
}

int g_large2idechs(tLARGE large_geometry, tIDECHS *idechs_geometry)
{
	tLBA lba_geom;
	g_large2lba(large_geometry, &lba_geom);
	g_lba2idechs(lba_geom, idechs_geometry);
	return 0;
}

int g_idechs2lba(tIDECHS idechs_geometry, tLBA *lba_geometry)
{
	*lba_geometry = idechs_geometry.c * idechs_geometry.h * idechs_geometry.s;
	return 0;
}

int g_idechs2chs(tIDECHS idechs_geometry, tCHS *chs_geometry)
{
	tLBA lba;
	g_idechs2lba(idechs_geometry, &lba);
	g_lba2chs(lba, chs_geometry);
	return 0;
}

int g_idechs2large(tIDECHS idechs_geometry, tLARGE *large_geometry)
{
	tLBA lba;
	g_idechs2lba(idechs_geometry, &lba);
	g_lba2large(lba, large_geometry);
	return 0;
}

int a_lba2chs(tCHS chs_geom, tLBA lba, tCHS *chs)
{
	chs->c = (uint16_t) ((lba / chs_geom.s) / chs_geom.h);
	chs->h = (uint8_t) ((lba / chs_geom.s) % chs_geom.h);
	chs->s = (uint8_t) ((lba % chs_geom.s) + 1);
	return 0;
}

int a_lba2idechs(tIDECHS chs_geom, tLBA lba, tIDECHS *chs)
{
	chs->s = (uint8_t) ((lba % chs_geom.s) + 1);
	chs->h = (uint8_t) ((lba / chs_geom.s) % chs_geom.h);
	chs->c = (uint16_t) ((lba / chs_geom.s) / chs_geom.h);
	return 0;
}

int a_lba2large(tLARGE chs_geom, tLBA lba, tLARGE *chs)
{
	chs->s = (uint8_t) ((lba % chs_geom.s) + 1);
	chs->h = (uint8_t) ((lba / chs_geom.s) % chs_geom.h);
	chs->c = (uint16_t) ((lba / chs_geom.s) / chs_geom.h);
	return 0;
}

int a_chs2lba(tCHS geom, tCHS chs, tLBA *lba)
{
	*lba = (uint32_t) (chs.c * geom.h + chs.h) * geom.s + chs.s - 1;
	return 0;
}

int a_chs2large(tCHS c_geom, tLARGE l_geom, tCHS chs, tLARGE *large)
{
	tLBA lba;
	a_chs2lba(c_geom, c_geom, &lba);
	a_lba2large(l_geom, lba, large);
	return 0;
}

int a_chs2idechs(tCHS c_geom, tIDECHS i_geom, tCHS chs, tIDECHS *idechs)
{
	tLBA lba;
	a_chs2lba(c_geom, c_geom, &lba);
	a_lba2idechs(i_geom, lba, idechs);
	return 0;
}

int a_idechs2lba(tIDECHS geom, tIDECHS chs, tLBA *lba)
{
	*lba = (uint32_t) (chs.c * geom.h + chs.h * geom.s + chs.s - 1);
	return 0;
}

int a_idechs2chs(tIDECHS i_geom, tCHS c_geom, tIDECHS idechs, tCHS *chs)
{
	tLBA lba;
	a_idechs2lba(i_geom, idechs, &lba);
	a_lba2chs(c_geom, lba, chs);
	return 0;
}

int a_idechs2large(tIDECHS i_geom, tLARGE l_geom, tIDECHS idechs, tLARGE *chs)
{
	tLBA lba;
	a_idechs2lba(i_geom, idechs, &lba);
	a_lba2large(l_geom, lba, chs);
	return 0;
}

int a_large2lba(tLARGE geom, tLARGE chs, tLBA *lba)
{
	*lba = (uint32_t) (chs.c * geom.h + chs.h * geom.s + chs.s - 1);
	return 0;
}

int a_large2chs(tLARGE l_geom, tCHS c_geom, tLARGE large, tCHS *chs)
{
	tLBA lba;
	a_large2lba(l_geom, large, &lba);
	a_lba2chs(c_geom, lba, chs);
	return 0;
}

int a_large2idechs(tLARGE l_geom, tIDECHS i_geom, tLARGE large, tIDECHS *chs)
{
	tLBA lba;
	a_large2lba(l_geom, large, &lba);
	a_lba2idechs(i_geom, lba, chs);
	return 0;
}