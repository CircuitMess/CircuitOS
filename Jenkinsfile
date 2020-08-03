pipeline {
    agent any

    stages {
        stage("Link") {
            steps {
                echo 'Linking...'
                sh 'echo $(pwd)'
                sh 'rm ~/Arduino/libraries/${PWD##*/}'
                sh 'ln -s $(pwd) ~/Arduino/libraries/${PWD##*/}'
            }
        }
    
        stage('Build') {
            steps {
                echo 'Building...'
                sh 'mkdir -p CircuitOS'
                sh 'cp CircuitOS.ino CircuitOS/'
                sh 'cd CircuitOS && ~/.arduino/arduino-cli compile -b cm:esp32:ringo -n CircuitOS.ino'
            }
        }
    }
}

