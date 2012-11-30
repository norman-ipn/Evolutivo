/******************************************************************************
*																			  *
*								TIEMPO										  *
*																			  *
*******************************************************************************/

int ResetTimeBase(Uint32 ini) 
{
	ini = SDL_GetTicks();
	return ini;
}

int CurrentTime(Uint32 fin, Uint32 ini) 
{
	fin = SDL_GetTicks();
	return fin - ini;
}
