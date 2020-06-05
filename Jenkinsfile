pipeline {
    agent any
    stages {
        stage('Build') {
            steps {
                echo 'Building...'
		        sh 'bazel build //...'
            }
        }
        stage('Test') {
            steps {
                echo 'Testing...'
                sh 'bazel test --keep_going --nocache_test_results //...'
            }
        }
    }
}
