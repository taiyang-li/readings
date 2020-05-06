#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <stack>
#include <sstream>
#include <fstream>
#include <time.h>
#include <algorithm>
#include <cmath>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <iostream>
#include <sstream>
#include <set>
#include <windows.h>

using namespace std;

#define MAXPRODUCT 100  // 最多产品数目
#define BUFSIZE 4  // product buffer size
HANDLE g_hThreads[2];
HANDLE g_hNotFullEvent = NULL;  
HANDLE g_hNotEmptyEvent = NULL;
HANDLE g_hMutex = NULL;

int g_iStorageCnt = 0; // product count in a buffer
int g_iProductIdx = 0; // index of the last produced product 
int g_iConsumeIdx = 0; // index of the last consumed product 


DWORD WINAPI ProduceThreadProc(LPVOID lpParam) 
{
        DWORD dwWaitResult = 0;

        // two objects.
        // Mutex and Not full event.
        HANDLE hObjects[2] = {NULL, NULL};
        hObjects[0] = g_hMutex;
        hObjects[1] = g_hNotFullEvent;

        for (int iIdx = 0; iIdx < MAXPRODUCTCNT; iIdx++)
        {
            //Wait till Mutex and Not full event are set signaled.
            dwWaitResult = WaitForMultipleObjects( 
                2, // number of handles in array
                hObjects, // array of handles
                TRUE, // wait till all are signaled
                INFINITE); // indefinite wait
            if (WAIT_OBJECT_0 != dwWaitResult)
            {
                printf("Wait error: (%d)\n", GetLastError()); 
                ExitThread(0); 
                }

            // Create a Product
            g_iProductIdx++;
            g_iStorageCnt++;
            printf("Create Product %d\n", g_iProductIdx);

            // check whether product buffer is full
            if (g_iStorageCnt >= BUFSIZE)
            {
                if (!ResetEvent(g_hNotFullEvent) ) 
                { 
                    printf("SetEvent failed (%d)\n", GetLastError());
                    ExitThread(0);
                    } 
                }

            // set not empty event signaled.
            if (!SetEvent(g_hNotEmptyEvent) ) 
            { 
                printf("SetEvent failed (%d)\n", GetLastError());
                ExitThread(0);
                } 

            // Release mutex
            ReleaseMutex(g_hMutex);
            }

        return 1;
        }

DWORD WINAPI ConsumeThreadProc(LPVOID lpParam) 
{
        DWORD dwWaitResult = 0;

        // two objects.
        // Mutex and Not empty event.
        HANDLE hObjects[2] = {NULL, NULL};
        hObjects[0] = g_hMutex;
        hObjects[1] = g_hNotEmptyEvent;


        for (int iIdx = 0; iIdx < MAXPRODUCTCNT; iIdx++)
        {
            //Wait till Mutex and Not empty event are set signaled.
            dwWaitResult = WaitForMultipleObjects( 
                2, // number of handles in array
                hObjects, // array of handles
                TRUE, // wait till all are signaled
                INFINITE); // indefinite wait
            if (WAIT_OBJECT_0 != dwWaitResult)
            {
                printf("Wait error: (%d)\n", GetLastError()); 
                ExitThread(0); 
                }

            // Consume a Product
            g_iStorageCnt--;
            g_iConsumeIdx++;
            printf("Consume product %d(%d)\n", g_iConsumeIdx, g_iProductIdx);

            // check whether product buffer is empty
            if (g_iStorageCnt < 1)
            {
                if (!ResetEvent(g_hNotEmptyEvent) ) 
                { 
                    printf("SetEvent failed (%d)\n", GetLastError());
                    ExitThread(0);
                    } 
                }

            /*set not full event signaled*/
            if (!SetEvent(g_hNotFullEvent) ) 
            { 
                printf("SetEvent failed (%d)\n", GetLastError());
                ExitThread(0);
                } 

            //Release mutex
            ReleaseMutex(g_hMutex);

            }

        return 1;
}

void main()
{
        DWORD dwThreadID[2] = {0, 0}; 

        // Create a manual-reset event object.
        // set this to signaled when the product buffer is not empty.
        g_hNotEmptyEvent = CreateEvent( 
            NULL, // default security attributes
            TRUE, // manual-reset event
            FALSE, // initial state is nonsignaled
            NULL // unnamed Event
            ); 
        if (NULL == g_hNotEmptyEvent) 
        { 
            printf("CreateEvent failed (%d)\n", GetLastError());
            return;
            }

        // Create a manual-reset event object.
        // set this to signaled when the product buffer is not full.
        g_hNotFullEvent = CreateEvent( 
            NULL, // default security attributes
            TRUE, // manual-reset event
            TRUE, // initial state is signaled
            NULL // unnamed Event
            ); 
        if (NULL == g_hNotFullEvent) 
        { 
            printf("CreateEvent failed (%d)\n", GetLastError());
            return;
            }


        // Create a mutex with no initial owner
        g_hMutex = CreateMutex( 
            NULL, // default security attributes
            FALSE, // initially not owned
            NULL); // unnamed mutex
        if (NULL == g_hMutex) 
        {
            printf("CreateMutex error: (%d)\n", GetLastError());
            return;
            }

        // Create a thread to produce products.
        g_hThreads[0] = CreateThread(NULL, 
            0, 
            ProduceThreadProc, 
            NULL,
            0, 
            &dwThreadID[0]); 
        if (NULL == g_hThreads[0]) 
{
        printf("CreateThread failed (%d)\n", GetLastError());
        return;
        }

// Create a thred to consume products.
g_hThreads[1] = CreateThread(NULL, 
        0, 
        ConsumeThreadProc, 
        NULL,
        0, 
        &dwThreadID[1]); 

if (g_hThreads[1] == NULL) 
{
        printf("CreateThread failed (%d)\n", GetLastError());
        return;
        }


DWORD dwWaitResult = WaitForMultipleObjects( 
        2, // number of handles in array
        g_hThreads, // array of thread handles
        TRUE, // wait till all threads quit
        INFINITE); // indefinite wait
if (WAIT_OBJECT_0 != dwWaitResult)
{ 
        printf("Wait error : (%d)\n", GetLastError()); 
        return;
        }

CloseHandle(g_hThreads[0]);
CloseHandle(g_hThreads[1]);
CloseHandle(g_hNotFullEvent);
CloseHandle(g_hNotEmptyEvent);
CloseHandle(g_hMutex);


}


