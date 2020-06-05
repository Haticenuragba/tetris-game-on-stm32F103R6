/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
RTC_HandleTypeDef hrtc;
int matrix[8][5];
int currentShapeType;
int rotateCount = 0;
int miliseconds = 0;

struct point{
	int row;
	int col;
};

struct point currentShape[4];

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_RTC_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void pushShapeToMatrix(){
int i=0; 
for(i=0; i<4; i++){
	if((currentShape[i].row != -1) && (currentShape[i].col != -1)){
		matrix[currentShape[i].row][currentShape[i].col] = 0;
	}
}
}

int generateShape(){
rotateCount = 0;
currentShapeType = rand() % 6;
//SHORT I
if(currentShapeType == 0 || currentShapeType == 5){
	if(matrix[7][2] == 0 || matrix[6][2] == 0) return 1;
	currentShape[0].row = 7;
	currentShape[0].col = 2;
	currentShape[1].row = 6;
	currentShape[1].col = 2;
	currentShape[2].row = -1;
	currentShape[2].col = -1;
	currentShape[3].row = -1;
	currentShape[3].col = -1;
	
}

//LONG I
else if(currentShapeType == 1){
	if(matrix[7][2] == 0 || matrix[6][2] == 0 || matrix[5][2] == 0) return 1;
	currentShape[0].row = 7;
	currentShape[0].col = 2;
	currentShape[1].row = 6;
	currentShape[1].col = 2;
	currentShape[2].row = 5;
	currentShape[2].col = 2;
	currentShape[3].row = -1;
	currentShape[3].col = -1;
}
// L
else if(currentShapeType == 2){
	if(matrix[7][2] == 0 || matrix[6][2] == 0 || matrix[6][3] == 0) return 1;
	currentShape[0].row = 7;
	currentShape[0].col = 2;
	currentShape[1].row = 6;
	currentShape[1].col = 2;
	currentShape[2].row = 6;
	currentShape[2].col = 3;
	currentShape[3].row = -1;
	currentShape[3].col = -1;
}

// Z
else if(currentShapeType == 3){
	if(matrix[7][2] == 0 || matrix[6][2] == 0 || matrix[6][3] == 0 || matrix[5][3] == 0) return 1;
	currentShape[0].row = 7;
	currentShape[0].col = 2;
	currentShape[1].row = 6;
	currentShape[1].col = 2;
	currentShape[2].row = 6;
	currentShape[2].col = 3;
	currentShape[3].row = 5;
	currentShape[3].col = 3;
}

// SQUARE

else{
	if(matrix[7][2] == 0 || matrix[6][2] == 0 || matrix[6][3] == 0 || matrix[7][3] == 0) return 1;
	currentShape[0].row = 7;
	currentShape[0].col = 2;
	currentShape[1].row = 6;
	currentShape[1].col = 2;
	currentShape[2].row = 6;
	currentShape[2].col = 3;
	currentShape[3].row = 7;
	currentShape[3].col = 3;
}


//PUSH SHAPE TO MATRIX
pushShapeToMatrix();
return 0;
}

int checkRowOfShape(int k, int c){
	int i=0;
	for(i=0; i<4; i++){
		if((currentShape[i].row != -1) && (currentShape[i].col != -1)){
		if(currentShape[i].row == k && currentShape[i].col == c){
			return 1;
		}
	}
	}
	return 0;
}

int checkSettled(){
	int i=0;
	for(i=0; i<4; i++){
		if((currentShape[i].row != -1) && (currentShape[i].col != -1)){
			int check = checkRowOfShape(currentShape[i].row - 1, currentShape[i].col);
			if((matrix[currentShape[i].row - 1][currentShape[i].col] == 0) && check == 0){
				return 1;
			}
			if(currentShape[i].row == 0){
				return 1;
			}
		}
	}
	return 0;
}

void cleanBackShape(){
	int i=0;
	for(i=0; i<4; i++){
		if((currentShape[i].row != -1) && (currentShape[i].col != -1)){
			matrix[currentShape[i].row][currentShape[i].col] = 1;
		}
	}
}

int shiftBelow(){
	cleanBackShape();
	int i=0;
	int n=0, k=0;
	for(i=0; i<4; i++){
		if((currentShape[i].row != -1) && (currentShape[i].col != -1)){
			k++;
			if((matrix[currentShape[i].row - 1][currentShape[i].col] == 1) && (currentShape[i].row - 1 >= 0)){
				n++;
			}
		}
	}
	if(k == n){
		for(i=0; i<4; i++){
			if((currentShape[i].row != -1) && (currentShape[i].col != -1)){
				currentShape[i].row --;
			}
		}
		pushShapeToMatrix();
		return 1;
	}
	else{
		pushShapeToMatrix();
		return 0;
	}
	/*cleanBackShape();
	int i=0;
	for(i=0; i<4; i++){
		if((currentShape[i].row != -1) && (currentShape[i].col != -1)){
			currentShape[i].row --;
		}
	}
	pushShapeToMatrix();
	*/
}

void resetMatrix(){
int i=0;
int j=0;
for(i=0; i<10; i++){
	for(j=0; j<5; j++){
		matrix[i][j] = 1;
	}
}
}
void setAllLeds(){
	// ROW 1
	HAL_GPIO_WritePin(GPIOA, _1A_Pin, matrix[0][0]);
	HAL_GPIO_WritePin(GPIOA, _1B_Pin, matrix[0][1]);
	HAL_GPIO_WritePin(GPIOA, _1C_Pin, matrix[0][2]);
	HAL_GPIO_WritePin(GPIOA, _1D_Pin, matrix[0][3]);
	HAL_GPIO_WritePin(GPIOA, _1E_Pin, matrix[0][4]);
	
	// ROW 2
	HAL_GPIO_WritePin(GPIOA, _2A_Pin, matrix[1][0]);
	HAL_GPIO_WritePin(GPIOA, _2B_Pin, matrix[1][1]);
	HAL_GPIO_WritePin(GPIOA, _2C_Pin, matrix[1][2]);
	HAL_GPIO_WritePin(GPIOA, _2D_Pin, matrix[1][3]);
	HAL_GPIO_WritePin(GPIOA, _2E_Pin, matrix[1][4]);
	
	// ROW 3
	HAL_GPIO_WritePin(GPIOA, _3A_Pin, matrix[2][0]);
	HAL_GPIO_WritePin(GPIOA, _3B_Pin, matrix[2][1]);
	HAL_GPIO_WritePin(GPIOA, _3C_Pin, matrix[2][2]);
	HAL_GPIO_WritePin(GPIOA, _3D_Pin, matrix[2][3]);
	HAL_GPIO_WritePin(GPIOA, _3E_Pin, matrix[2][4]);
	
	// ROW 4
	HAL_GPIO_WritePin(GPIOB, _4A_Pin, matrix[3][0]);
	HAL_GPIO_WritePin(GPIOB, _4B_Pin, matrix[3][1]);
	HAL_GPIO_WritePin(GPIOB, _4C_Pin, matrix[3][2]);
	HAL_GPIO_WritePin(GPIOB, _4D_Pin, matrix[3][3]);
	HAL_GPIO_WritePin(GPIOB, _4E_Pin, matrix[3][4]);
	
	// ROW 5
	HAL_GPIO_WritePin(GPIOB, _5A_Pin, matrix[4][0]);
	HAL_GPIO_WritePin(GPIOB, _5B_Pin, matrix[4][1]);
	HAL_GPIO_WritePin(GPIOB, _5C_Pin, matrix[4][2]);
	HAL_GPIO_WritePin(GPIOB, _5D_Pin, matrix[4][3]);
	HAL_GPIO_WritePin(GPIOB, _5E_Pin, matrix[4][4]);
	
	// ROW 6
	HAL_GPIO_WritePin(GPIOB, _6A_Pin, matrix[5][0]);
	HAL_GPIO_WritePin(GPIOB, _6B_Pin, matrix[5][1]);
	HAL_GPIO_WritePin(GPIOB, _6C_Pin, matrix[5][2]);
	HAL_GPIO_WritePin(GPIOB, _6D_Pin, matrix[5][3]);
	HAL_GPIO_WritePin(GPIOB, _6E_Pin, matrix[5][4]);
	
	// ROW 7
	HAL_GPIO_WritePin(GPIOB, _7A_Pin, matrix[6][0]);
	HAL_GPIO_WritePin(GPIOC, _7B_Pin, matrix[6][1]);
	HAL_GPIO_WritePin(GPIOC, _7C_Pin, matrix[6][2]);
	HAL_GPIO_WritePin(GPIOC, _7D_Pin, matrix[6][3]);
	HAL_GPIO_WritePin(GPIOC, _7E_Pin, matrix[6][4]);
		
	// ROW 8
	HAL_GPIO_WritePin(GPIOC, _8A_Pin, matrix[7][0]);
	HAL_GPIO_WritePin(GPIOC, _8B_Pin, matrix[7][1]);
	HAL_GPIO_WritePin(GPIOC, _8C_Pin, matrix[7][2]);
	HAL_GPIO_WritePin(GPIOC, _8D_Pin, matrix[7][3]);
	HAL_GPIO_WritePin(GPIOC, _8E_Pin, matrix[7][4]);
	
}
void rotateShortI(){
cleanBackShape();
int nRotate = rotateCount % 2;
if(nRotate == 0){
if((matrix[currentShape[1].row + 1][currentShape[1].col + 1] == 1) && (currentShape[1].row + 1 <=7) && (currentShape[1].col + 1 <=4)){
	currentShape[1].col++;
	currentShape[1].row++;
	rotateCount++;
}
}
else{
if((matrix[currentShape[1].row - 1][currentShape[1].col - 1] == 1) && (currentShape[1].row - 1 >=0) && (currentShape[1].col - 1 >= 0)){
	currentShape[1].col--;
	currentShape[1].row--;
	rotateCount++;
}
}	
}
void rotateLongI(){
cleanBackShape();
int nRotate = rotateCount % 2;
if(nRotate == 0){
if((matrix[currentShape[0].row - 1][currentShape[0].col - 1] == 1) && (currentShape[0].row - 1 >=0) && (currentShape[0].col - 1 >= 0) &&
(matrix[currentShape[2].row + 1][currentShape[2].col + 1] == 1) && (currentShape[2].row + 1 <=7) && (currentShape[2].col + 1 <=4)	
){
	currentShape[0].col--;
	currentShape[0].row--;
	currentShape[2].col++;
	currentShape[2].row++;
	rotateCount++;
}
}
else{
if((matrix[currentShape[0].row + 1][currentShape[0].col + 1] == 1) && (currentShape[0].row + 1 <=7) && (currentShape[0].col + 1 <= 4) &&
(matrix[currentShape[2].row - 1][currentShape[2].col - 1] == 1) && (currentShape[2].row - 1 >=0) && (currentShape[2].col - 1 >=0)	
){
	currentShape[0].col++;
	currentShape[0].row++;
	currentShape[2].col--;
	currentShape[2].row--;
	rotateCount++;
}
}	
}
void rotateZ(){
	cleanBackShape();
    int nRotate = rotateCount % 2;
    if(nRotate == 0){
        if((matrix[currentShape[0].row - 1][currentShape[0].col - 1] == 1) && (matrix[currentShape[0].row][currentShape[0].col + 1] == 1) && currentShape[0].col - 1 >= 0){
            currentShape[0].col--;
            currentShape[0].row--;
            currentShape[2].col--;
            currentShape[2].row++;
            currentShape[3].row+=2;
				rotateCount++;
        }
    }else{
        if((matrix[currentShape[1].row][currentShape[1].col + 1] == 1) && (matrix[currentShape[1].row - 1][currentShape[0].col + 1] == 1) && currentShape[0].row - 1 >= 0){
            currentShape[0].col++;
            currentShape[0].row++;
            currentShape[2].col++;
            currentShape[2].row--;
            currentShape[3].row-=2;
				rotateCount++;
        }
    }
}

void rotateL(){
	cleanBackShape();
    int nRotate = rotateCount % 4;
    if(nRotate == 0){
        if(matrix[currentShape[2].row + 1][currentShape[2].col] == 1){
            currentShape[0].row--;
            currentShape[1].col++;
            currentShape[2].row++;
					rotateCount++;
        }

    }else if(nRotate == 1){
        if(matrix[currentShape[2].row][currentShape[2].col - 1] == 1){
            currentShape[0].col++;
            currentShape[1].row++;
            currentShape[2].col--;
					rotateCount++;
        }
    }else if (nRotate == 2) {
        if(matrix[currentShape[2].row - 1][currentShape[2].col] == 1){
            currentShape[0].row++;
            currentShape[1].col--;
            currentShape[2].row--;
					rotateCount++;
        }
    } else {
        if(matrix[currentShape[2].row - 1][currentShape[2].col + 1] == 1){
            currentShape[0].col--;
            currentShape[1].row--;
            currentShape[2].col++;
					rotateCount++;
        }
    }
}

void rotate(){
// SHORT I
if(currentShapeType == 0 || currentShapeType == 5){
	rotateShortI();
}

//LONG I
else if(currentShapeType == 1){
	rotateLongI();
}
// L
else if(currentShapeType == 2){
	rotateL();
}

// Z
else if(currentShapeType == 3){
	rotateZ();
}

pushShapeToMatrix();
}

void removeRow(){
	int i,j, rows=0;
	for(i=0; i<8; i++){
		int k = 0;
		for(j=0; j<5; j++){
			if(matrix[i][j] == 0)
				k++;
		}
		if(k == 5)
			rows++;
	}
	if(rows > 0){
	for(i=0; i<8-rows; i++){
		for(j=0; j<5; j++){
			matrix[i][j] = matrix[i+rows][j];
			matrix[i+rows][j] = 1;
		}
	}
}
}

void shiftLeft(){
cleanBackShape();
	int i=0;
	int n=0, k=0;
	for(i=0; i<4; i++){
		if((currentShape[i].row != -1) && (currentShape[i].col != -1)){
			k++;
			if((matrix[currentShape[i].row][currentShape[i].col - 1] == 1) && (currentShape[i].col - 1 >= 0)){
				n++;
			}
		}
	}
	if(k == n){
		for(i=0; i<4; i++){
			if((currentShape[i].row != -1) && (currentShape[i].col != -1)){
				currentShape[i].col --;
			}
		}
		pushShapeToMatrix();
	}
}

void shiftRight(){
cleanBackShape();
	int i=0;
	int n=0, k=0;
	for(i=0; i<4; i++){
		if((currentShape[i].row != -1) && (currentShape[i].col != -1)){
			k++;
			if((matrix[currentShape[i].row][currentShape[i].col + 1] == 1) && (currentShape[i].col + 1 <= 4)){
				n++;
			}
		}
	}
	if(k == n){
		for(i=0; i<4; i++){
			if((currentShape[i].row != -1) && (currentShape[i].col != -1)){
				currentShape[i].col ++;
			}
		}
		pushShapeToMatrix();
	}
}

void gameOver(){
	
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
	
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */
	
  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_RTC_Init();
  /* USER CODE BEGIN 2 */
	srand(5);
	resetMatrix();
	generateShape();
	setAllLeds();
	
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */
		HAL_Delay(500);
		int check = shiftBelow();
		setAllLeds();
		if(check == 0){ // if shape is settled create new one
			removeRow();
			setAllLeds();
			int res = generateShape();
			if(res == 0)
				setAllLeds();
			else{
				gameOver();
				break;
			}
		}
		
    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_LSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_RTC;
  PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSI;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief RTC Initialization Function
  * @param None
  * @retval None
  */
static void MX_RTC_Init(void)
{

  /* USER CODE BEGIN RTC_Init 0 */

  /* USER CODE END RTC_Init 0 */

  RTC_TimeTypeDef sTime = {0};
  RTC_DateTypeDef DateToUpdate = {0};
  RTC_AlarmTypeDef sAlarm = {0};

  /* USER CODE BEGIN RTC_Init 1 */

  /* USER CODE END RTC_Init 1 */
  /** Initialize RTC Only 
  */
  hrtc.Instance = RTC;
  hrtc.Init.AsynchPrediv = RTC_AUTO_1_SECOND;
  hrtc.Init.OutPut = RTC_OUTPUTSOURCE_ALARM;
  if (HAL_RTC_Init(&hrtc) != HAL_OK)
  {
    Error_Handler();
  }

  /* USER CODE BEGIN Check_RTC_BKUP */
    
  /* USER CODE END Check_RTC_BKUP */

  /** Initialize RTC and set the Time and Date 
  */
  sTime.Hours = 0x0;
  sTime.Minutes = 0x0;
  sTime.Seconds = 0x0;

  if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BCD) != HAL_OK)
  {
    Error_Handler();
  }
  DateToUpdate.WeekDay = RTC_WEEKDAY_MONDAY;
  DateToUpdate.Month = RTC_MONTH_JANUARY;
  DateToUpdate.Date = 0x1;
  DateToUpdate.Year = 0x0;

  if (HAL_RTC_SetDate(&hrtc, &DateToUpdate, RTC_FORMAT_BCD) != HAL_OK)
  {
    Error_Handler();
  }
  /** Enable the Alarm A 
  */
  sAlarm.AlarmTime.Hours = 0x0;
  sAlarm.AlarmTime.Minutes = 0x0;
  sAlarm.AlarmTime.Seconds = 0x0;
  sAlarm.Alarm = RTC_ALARM_A;
  if (HAL_RTC_SetAlarm_IT(&hrtc, &sAlarm, RTC_FORMAT_BCD) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN RTC_Init 2 */

  /* USER CODE END RTC_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, _7B_Pin|_7C_Pin|_7D_Pin|_7E_Pin 
                          |_8A_Pin|_8B_Pin|_8C_Pin|_8D_Pin 
                          |_8E_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, _1A_Pin|_1B_Pin|_1C_Pin|_1D_Pin 
                          |_1E_Pin|_2A_Pin|_2B_Pin|_2C_Pin 
                          |_2D_Pin|_2E_Pin|_3A_Pin|_3B_Pin 
                          |_3C_Pin|_3D_Pin|_3E_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, _4A_Pin|_4B_Pin|_4C_Pin|_6A_Pin 
                          |_6B_Pin|_6C_Pin|_6D_Pin|_6E_Pin 
                          |_7A_Pin|_4D_Pin|_4E_Pin|_5A_Pin 
                          |_5B_Pin|_5C_Pin|_5D_Pin|_5E_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : _7B_Pin _7C_Pin _7D_Pin _7E_Pin 
                           _8A_Pin _8B_Pin _8C_Pin _8D_Pin 
                           _8E_Pin */
  GPIO_InitStruct.Pin = _7B_Pin|_7C_Pin|_7D_Pin|_7E_Pin 
                          |_8A_Pin|_8B_Pin|_8C_Pin|_8D_Pin 
                          |_8E_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : _1A_Pin _1B_Pin _1C_Pin _1D_Pin 
                           _1E_Pin _2A_Pin _2B_Pin _2C_Pin 
                           _2D_Pin _2E_Pin _3A_Pin _3B_Pin 
                           _3C_Pin _3D_Pin _3E_Pin */
  GPIO_InitStruct.Pin = _1A_Pin|_1B_Pin|_1C_Pin|_1D_Pin 
                          |_1E_Pin|_2A_Pin|_2B_Pin|_2C_Pin 
                          |_2D_Pin|_2E_Pin|_3A_Pin|_3B_Pin 
                          |_3C_Pin|_3D_Pin|_3E_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : _4A_Pin _4B_Pin _4C_Pin _6A_Pin 
                           _6B_Pin _6C_Pin _6D_Pin _6E_Pin 
                           _7A_Pin _4D_Pin _4E_Pin _5A_Pin 
                           _5B_Pin _5C_Pin _5D_Pin _5E_Pin */
  GPIO_InitStruct.Pin = _4A_Pin|_4B_Pin|_4C_Pin|_6A_Pin 
                          |_6B_Pin|_6C_Pin|_6D_Pin|_6E_Pin 
                          |_7A_Pin|_4D_Pin|_4E_Pin|_5A_Pin 
                          |_5B_Pin|_5C_Pin|_5D_Pin|_5E_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : START_Pin LEFT_Pin R_GHT_Pin ROTATE_Pin */
  GPIO_InitStruct.Pin = START_Pin|LEFT_Pin|R_GHT_Pin|ROTATE_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI9_5_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);

  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

}

/* USER CODE BEGIN 4 */

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
UNUSED(GPIO_Pin);
	int tempMiliseconds = HAL_GetTick();
	if(tempMiliseconds - miliseconds <= 300){
		return;
	}
	miliseconds = HAL_GetTick();
	switch(GPIO_Pin){
		case START_Pin:   break;
		case ROTATE_Pin:  rotate(); break;
		case LEFT_Pin: shiftLeft(); break;
		case R_GHT_Pin: shiftRight(); break;
	}
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
