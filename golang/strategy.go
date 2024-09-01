package main

import "fmt"

type DrivingStrategy interface {
	Drive()
}

type FastDrivingStrategy struct {
}

func (f *FastDrivingStrategy) Drive() {
	fmt.Println("driving fast!")
}

type NormalDrivingStrategy struct {
}

func (n *NormalDrivingStrategy) Drive() {
	fmt.Println("normal driving!")
}

type Car interface {
	DriveCar()
}

type FamilyCar struct {
	strategy DrivingStrategy
}

func (f *FamilyCar) DriveCar() {
	f.strategy.Drive()
}

type RacingCar struct {
	strategy DrivingStrategy
}

func (r *RacingCar) DriveCar() {
	r.strategy.Drive()
}

func NewFamilyCar() Car {
	return &FamilyCar{strategy: &NormalDrivingStrategy{}}
}

func NewRacingCar() Car {
	return &RacingCar{strategy: &FastDrivingStrategy{}}
}

func main() {
	familyCar := NewFamilyCar()
	racingCar := NewRacingCar()

	familyCar.DriveCar()
	racingCar.DriveCar()
}
