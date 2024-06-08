package main

import (
    "encoding/csv"
    "fmt"
    "flag"
    "os"
)

func processRecord(record string) {
    // TODO: due to our upstream processing only the last character isn't allowed to be a space
    if record[len(record)-1:] == " " {
        fmt.Println("Error: Bad value encountered!")
        os.Exit(1)
    }
    // fmt.Printf("Processing record: %v\n", record) // for debug
}

func main() {
    data := flag.String("data", "good", "what data to process")
    flag.Parse()

    file, err := os.Open(*data + ".csv")
    if err != nil {
        panic(err)
    }
    defer file.Close()

    csvReader := csv.NewReader(file)
    for {
        record, err := csvReader.Read()
        if err != nil {
            break
        }
        processRecord(record[1])
    }
    fmt.Println("Data successfully processed!")
}
